#include <chrono>

class Benchmark
{
public:
    Benchmark();
    ~Benchmark();

    void Start();
    void Stop();

    double GetElapsedSeconds() const;
    double GetElapsedMilliseconds() const;
    double GetElapsedMicroseconds() const;

private:
    std::chrono::high_resolution_clock::time_point m_StartTime;
    std::chrono::high_resolution_clock::time_point m_EndTime;

    bool m_HasStopped{false};
};