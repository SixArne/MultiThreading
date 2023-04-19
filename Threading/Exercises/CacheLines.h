#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <limits>
#include <thread>
#include <span>

#include "Benchmarking/Benchmark.h"
#include "BaseExercise.h"

constexpr int DATASET_SIZE = 50'000'000;
constexpr int CACHE_LINE_SIZE = 64;
constexpr int CORES = 8;

class CacheLines: public BaseExercise
{
public:
    CacheLines();
    virtual ~CacheLines();

    virtual void Run() override;

private:
    void ProcessDataset(std::span<int> arr, int& sum);

    void WithCacheLines();
    void WithoutCacheLines();
};
