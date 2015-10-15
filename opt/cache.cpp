#include <iostream>

#include <vector>
#include <random>
#include <popcntintrin.h>

#include "benchmark/benchmark_api.h"

template <typename T>
char slow_cnt(T x) {
  char res = 0;
  while (x != 0) {
    res += x & 1;
    x >>= 1;
  }
  return res;
}

template <typename T>
class population_counter {
  std::vector<int> cache_;

public:

  population_counter() {
    typedef typename std::vector<T>::difference_type dt;
    dt min_ = std::numeric_limits<T>::min();
    dt max_ = std::numeric_limits<T>::max();
    cache_.reserve(max_ - min_ + 1);

    std::cout << "cache size is " << max_ - min_ << ", szof=" << sizeof(T) <<  "\n";

    for (dt i = min_; i <= max_; ++i) {
      dt idx = i - min_;
      cache_.push_back(slow_cnt(i));
    }
  }

  BENCHMARK_ALWAYS_INLINE int operator()(T val) const {
    return cache_[val];
  }
};

class Popcnt : public benchmark::Fixture {
protected:
  void* data_;
  const size_t datasize = 100 * 1024 * 1024; //100MB, won't fit in L2

public:
  Popcnt() {
    data_ = malloc(datasize);

    std::default_random_engine engine;
    using restype = decltype(engine());
    size_t totalsize = datasize / sizeof(restype);

    restype *ptr = reinterpret_cast<restype*>(data_);
    for (size_t i = 0; i < totalsize; ++i) {
      ptr[i] = engine();
    }
  }

  ~Popcnt() {
    free(data_);
  }
};

BENCHMARK_F(Popcnt, TableChar)(benchmark::State& st) {
  using mytype = unsigned char;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  population_counter<mytype> counter;
  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += counter(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(Popcnt, TableShort)(benchmark::State& st) {
  using mytype = unsigned short;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  population_counter<mytype> counter;
  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += counter(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(Popcnt, FuncChar)(benchmark::State& st) {
  using mytype = unsigned char;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += slow_cnt(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(Popcnt, FuncShort)(benchmark::State& st) {
  using mytype = unsigned short;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += slow_cnt(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(Popcnt, FuncInt)(benchmark::State& st) {
  using mytype = unsigned int;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += slow_cnt(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(Popcnt, FuncLong)(benchmark::State& st) {
  using mytype = unsigned long long;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += slow_cnt(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(Popcnt, AsmLong)(benchmark::State& st) {
  using mytype = unsigned long long;

  mytype *ptr = reinterpret_cast<mytype *>(data_);
  size_t mysize = this->datasize / sizeof(mytype);

  long res = 0;

  while (st.KeepRunning()) {
    for (size_t i = 0; i < mysize; ++i) {
      res += _mm_popcnt_u64(ptr[i]);
    }
  }
  benchmark::DoNotOptimize(res);
}

BENCHMARK_MAIN()