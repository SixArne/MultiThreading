#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <limits>
#include <thread>

#include "Benchmarking/Benchmark.h"

constexpr size_t DATASET_SIZE = 500000;

int main()
{
    std::minstd_rand rne{};
    std::vector<std::array<int, DATASET_SIZE>> datasets{4};
    std::vector<std::thread> workers{};

    auto benchmark = Benchmark{};
    for (auto& arr: datasets)
    {
        std::ranges::generate(arr, rne);
    }

    for (auto& set: datasets)
    {
        auto w = [&set]
        {
            for (int x: set)
            {
                constexpr auto limit = (double)std::numeric_limits<int>::max();
                const auto y = (double)x/ limit;

                set[0] += int(std::sin(std::cos(y)) * limit);
            }
        };

        workers.emplace_back(std::thread{w});
    }

    for (auto& w: workers)
    {
        w.join();
    }

    benchmark.Stop();

    return 0;
}