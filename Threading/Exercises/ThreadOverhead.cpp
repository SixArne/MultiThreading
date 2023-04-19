#include "ThreadOverhead.h"

#include <vector>
#include <array>
#include <random>
#include <span>
#include <limits>
#include <functional>
#include <numeric>
#include <iostream>

#include "Benchmarking/Benchmark.h"

void ThreadOverhead::Run()
{
    WithSomeThreads();
    WithLotsOfThreads();
}

void ThreadOverhead::WithLotsOfThreads()
{
    std::vector<std::array<int, DATASET_SIZE>> datasets{CORES};
    std::vector<std::jthread> workers{};

    std::minstd_rand rne{};

    for (auto& arr: datasets)
    {
        std::ranges::generate(arr, rne);
    }

    struct Value
    {
        int v;
        char padding[64 - sizeof(int)];
    };
    std::array<Value, CORES> sums{};


    std::cout << "-------------------" << std::endl;
    std::cout << "Multi threaded with lots of threads    " << std::endl;
    std::cout << "-------------------" << std::endl;
    auto benchmark = Benchmark{};


    constexpr auto subnetSize = DATASET_SIZE / 10'000;
    int total = 0;

    for (size_t i = 0; i < DATASET_SIZE; i += subnetSize)
    {
        for (size_t j{}; j < CORES; j++)
        {
            workers.emplace_back(std::jthread{&ThreadOverhead::ProcessDataset, this, std::span{&datasets[j][i], subnetSize}, std::ref(sums[j].v)});
        }
        workers.clear();
        total += std::accumulate(sums.begin(), sums.end(), 0, [](int a, Value b) { return a + b.v; });
    }

    benchmark.Stop();

    std::cout << "Total " << total << std::endl;
}

void ThreadOverhead::WithSomeThreads()
{
    std::vector<std::array<int, DATASET_SIZE>> datasets{CORES};
    std::vector<std::jthread> workers{};

    std::minstd_rand rne{};

    for (auto& arr: datasets)
    {
        std::ranges::generate(arr, rne);
    }

    struct Value
    {
        int v;
        char padding[64 - sizeof(int)];
    };
    std::array<Value, CORES> sums{};


    std::cout << "-------------------" << std::endl;
    std::cout << "Multi threaded with some threads    " << std::endl;
    std::cout << "-------------------" << std::endl;
    auto benchmark = Benchmark{};


    constexpr auto subnetSize = DATASET_SIZE / 1;
    int total = 0;

    for (size_t i = 0; i < DATASET_SIZE; i += subnetSize)
    {
        for (size_t j{}; j < CORES; j++)
        {
            workers.emplace_back(std::jthread{&ThreadOverhead::ProcessDataset, this, std::span{&datasets[j][i], subnetSize}, std::ref(sums[j].v)});
        }
        workers.clear();
        total += std::accumulate(sums.begin(), sums.end(), 0, [](int a, Value b) { return a + b.v; });
    }

    benchmark.Stop();

    std::cout << "Total " << total << std::endl;
}

void ThreadOverhead::ProcessDataset(std::span<int> arr, int& sum)
{
    for (int x: arr)
    {
        constexpr auto limit = (double)std::numeric_limits<int>::max();
        const auto y = (double)x/ limit;

        sum += int(std::sin(std::cos(y)) * limit);
    }
}