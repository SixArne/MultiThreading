#include "BaseExercise.h"

#include <span>

constexpr int DATASET_SIZE = 50'000'000;
constexpr int CORES = 8;

class ThreadOverhead: public BaseExercise
{
public:
    virtual void Run() override;

private:
    void WithLotsOfThreads();
    void WithSomeThreads();

    void ProcessDataset(std::span<int> arr, int& sum);
};

