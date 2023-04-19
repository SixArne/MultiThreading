#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <limits>
#include <thread>

//#include "Exercises/CacheLines.h"
#include "Exercises/ThreadOverhead.h"

int main()
{
    ThreadOverhead threadOverhead{};
    threadOverhead.Run();

    // CacheLines cacheLines{};
    // cacheLines.Run();
}