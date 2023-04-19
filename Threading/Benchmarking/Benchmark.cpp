#include "Benchmark.h"

#include <chrono>
#include <iostream>

Benchmark::Benchmark()
{
    Start();
}

Benchmark::~Benchmark()
{
    if (!m_HasStopped)
        Stop();
}

void Benchmark::Start()
{
    m_StartTime = std::chrono::high_resolution_clock::now();
}

void Benchmark::Stop()
{
    m_HasStopped = true;
    m_EndTime = std::chrono::high_resolution_clock::now();

    float precision = 4;

    std::cout << std::fixed << std::setprecision(precision) << "Elapsed seconds: "
              << GetElapsedSeconds()
              << " seconds" << std::endl;

    std::cout << std::fixed << std::setprecision(precision) << "Elapsed milliseconds: "
              << GetElapsedMilliseconds()
              << " milliseconds" << std::endl;

    std::cout << std::fixed << std::setprecision(precision) << "Elapsed microseconds: "
              << GetElapsedMicroseconds()
              << " microseconds" << std::endl;
}

double Benchmark::GetElapsedSeconds() const
{
    return std::chrono::duration<double>(m_EndTime - m_StartTime).count();
}

double Benchmark::GetElapsedMilliseconds() const
{
    return std::chrono::duration<double, std::milli>(m_EndTime - m_StartTime).count();
}

double Benchmark::GetElapsedMicroseconds() const
{
    return std::chrono::duration<double, std::micro>(m_EndTime - m_StartTime).count();
}

