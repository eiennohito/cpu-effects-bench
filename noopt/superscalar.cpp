//
// Created by Arseny Tolmachev on 2015/10/15.
//

#include <iostream>
#include <vector>
#include <random>
#include "benchmark/benchmark_api.h"

double sum1(double* vals, size_t cnt) {
  double res = 0;
  for (size_t i = 0; i < cnt; i += 1) {
    res += vals[i];
  }
  return res;
}

double sum2(double* vals, size_t cnt) {
  double res1 = 0, res2 = 0;
  for (size_t i = 0; i < cnt; i += 2) {
    res1 += vals[i];
    res2 += vals[i + 1];
  }
  return res1 + res2;
}

double sum3(double* vals, size_t cnt) {
  double
      res1 = 0,
      res2 = 0,
      res3 = 0;
  for (size_t i = 0; i < cnt; i += 3) {
    res1 += vals[i];
    res2 += vals[i + 1];
    res3 += vals[i + 2];
  }
  return res1 + res2 + res3;
}

double sum4(double* vals, size_t cnt) {
  double res1 = 0, res2 = 0, res3 = 0, res4 = 0;
  for (size_t i = 0; i < cnt; i += 4) {
    res1 += vals[i];
    res2 += vals[i + 1];
    res3 += vals[i + 2];
    res4 += vals[i + 3];
  }
  return res1 + res2 + res3 + res4;
}

double sum8(double* vals, size_t cnt) {
  double res1 = 0, res2 = 0, res3 = 0, res4 = 0;
  double res5 = 0, res6 = 0, res7 = 0, res8 = 0;
  for (size_t i = 0; i < cnt; i += 8) {
    res1 += vals[i];
    res2 += vals[i + 1];
    res3 += vals[i + 2];
    res4 += vals[i + 3];
    res5 += vals[i + 4];
    res6 += vals[i + 5];
    res7 += vals[i + 6];
    res8 += vals[i + 7];
  }
  return res1 + res2 + res3 + res4 + res5 + res6 + res7 + res8;
}

class SumFixture : public ::benchmark::Fixture {
protected:
  std::vector<double> data_;

public:
  SumFixture() {
    data_ = std::vector<double>(50400000); //divides by all numbers from 1 to 8
    std::default_random_engine eng;
    std::normal_distribution<double> distr;
    std::generate(std::begin(data_), std::end(data_), [&](){ return distr(eng); });
  }
};

BENCHMARK_F(SumFixture, By1)(benchmark::State& st) {
  double res = 0;
  size_t processed = 0;
  while (st.KeepRunning()) {
    res += sum1(data_.data(), data_.size());
    processed += data_.size();
  }
  st.SetItemsProcessed(processed);
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(SumFixture, By2)(benchmark::State& st) {
  double res = 0;
  size_t processed = 0;
  while (st.KeepRunning()) {
    res += sum2(data_.data(), data_.size());
    processed += data_.size();
  }
  st.SetItemsProcessed(processed);
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(SumFixture, By3)(benchmark::State& st) {
  double res = 0;
  size_t processed = 0;
  while (st.KeepRunning()) {
    res += sum3(data_.data(), data_.size());
    processed += data_.size();
  }
  st.SetItemsProcessed(processed);
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(SumFixture, By4)(benchmark::State& st) {
  double res = 0;
  size_t processed = 0;
  while (st.KeepRunning()) {
    res += sum4(data_.data(), data_.size());
    processed += data_.size();
  }
  st.SetItemsProcessed(processed);
  benchmark::DoNotOptimize(res);
}

BENCHMARK_F(SumFixture, By8)(benchmark::State& st) {
  double res = 0;
  size_t processed = 0;
  while (st.KeepRunning()) {
    res += sum8(data_.data(), data_.size());
    processed += data_.size();
  }
  st.SetItemsProcessed(processed);
  benchmark::DoNotOptimize(res);
}

BENCHMARK_MAIN()