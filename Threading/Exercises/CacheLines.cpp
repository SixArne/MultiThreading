#include "CacheLines.h"

#include <span>

CacheLines::CacheLines()
{
}

CacheLines::~CacheLines()
{
}

void CacheLines::Run()
{
    WithCacheLines();
    WithoutCacheLines();
}

void CacheLines::WithCacheLines()
{
    std::cout << "-------------------" << std::endl;
    std::cout << "Different Cacheline" << std::endl;
    std::cout << "-------------------" << std::endl;

    std::minstd_rand rne{};
    std::vector<std::array<int, DATASET_SIZE>> datasets{CORES};
    std::vector<std::thread> workers{};

    for (auto& arr: datasets)
    {
        std::ranges::generate(arr, rne);
    }

    struct Value
    {
        int v;
        char padding[CACHE_LINE_SIZE - sizeof(int)];
    };
    std::array<Value, CORES> sums{};
    auto benchmark = Benchmark{};

    for (size_t i{}; i < datasets.size(); ++i)
    {
        workers.emplace_back(std::thread{&CacheLines::ProcessDataset, this, std::span{datasets[i]}, std::ref(sums[i].v)});
    }

    for (auto& w: workers)
    {
        w.join();
    }

    benchmark.Stop();
}

void CacheLines::WithoutCacheLines()
{
    std::cout << "-------------------" << std::endl;
    std::cout << "Same Cacheline     " << std::endl;
    std::cout << "-------------------" << std::endl;

    std::minstd_rand rne{};
    std::vector<std::array<int, DATASET_SIZE>> datasets{CORES};
    std::vector<std::thread> workers{};

    for (auto& arr: datasets)
    {
        std::ranges::generate(arr, rne);
    }

    struct Value
    {
        int v;
    };
    std::array<Value, CORES> sums{};
    auto benchmark = Benchmark{};

    for (size_t i{}; i < datasets.size(); ++i)
    {
        workers.emplace_back(std::thread{&CacheLines::ProcessDataset, this, std::span{datasets[i]}, std::ref(sums[i].v)});
    }

    for (auto& w: workers)
    {
        w.join();
    }

    benchmark.Stop();
}

void CacheLines::ProcessDataset(std::span<int> arr, int& sum)
{
    for (int x: arr)
    {
        constexpr auto limit = (double)std::numeric_limits<int>::max();
        const auto y = (double)x/ limit;

        sum += int(std::sin(std::cos(y)) * limit);
    }
}