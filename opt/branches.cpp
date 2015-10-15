//
// Created by Arseny Tolmachev on 2015/10/15.
//

#include <vector>
#include <random>
#include "benchmark/benchmark_api.h"

//http://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-an-unsorted-array

class Ints : public benchmark::Fixture {
protected:
  std::vector<int> data_;
  const size_t datasize = 1000000;

public:
  Ints() {
    std::default_random_engine rng;
    std::uniform_int_distribution<int> dist(0, 256);
    std::generate_n(std::back_inserter(data_), datasize, [&](){ return dist(rng); });
  }
};

BENCHMARK_F(Ints, JustSum)(benchmark::State &st) {
  long long less = 0, more = 0;
  while (st.KeepRunning()) {
    for (size_t i = 0; i < datasize; ++i) {
      auto val = data_[i];
      if (val > 127) { //odd
        more += 1;
      } else {
        less += 1;
      }
    }
  }
  benchmark::DoNotOptimize(less);
  benchmark::DoNotOptimize(more);
}

BENCHMARK_F(Ints, SortSum)(benchmark::State &st) {
  long long less = 0, more = 0;
  std::sort(data_.begin(), data_.end());
  while (st.KeepRunning()) {
    for (size_t i = 0; i < datasize; ++i) {
      auto val = data_[i];
      if (val > 127) { //odd
        more += 1;
      } else {
        less += 1;
      }
    }
  }
  benchmark::DoNotOptimize(less);
  benchmark::DoNotOptimize(more);
}

BENCHMARK_MAIN()