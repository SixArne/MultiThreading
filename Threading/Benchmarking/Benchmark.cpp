#include "Benchmark.h"

#include <chrono>
#include <iostream>

Benchmark::Benchmark()
{
    Start();
}

Benchmark::~Benchmark()
{
    Stop();
}

void Benchmark::Start()
{
    m_StartTime = std::chrono::high_resolution_clock::now();
}

void Benchmark::Stop()
{
    m_EndTime = std::chrono::high_resolution_clock::now();

    std::cout << "Elapsed seconds: " << GetElapsedSeconds() << " seconds" << std::endl;
    std::cout << "Elapsed milliseconds: " << GetElapsedMilliseconds() << " milliseconds" << std::endl;
    std::cout << "Elapsed microseconds: " << GetElapsedMicroseconds() << " microseconds" << std::endl;
}

double Benchmark::GetElapsedSeconds() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(m_EndTime - m_StartTime).count();
}

double Benchmark::GetElapsedMilliseconds() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime).count();
}

double Benchmark::GetElapsedMicroseconds() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime).count();
}

