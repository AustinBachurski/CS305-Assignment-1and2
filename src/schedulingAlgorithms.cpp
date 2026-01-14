#include "schedulingAlgorithms.hpp"
#include "process.hpp"

// Functions are described with comments in `schedulingAlgorithms.hpp`.

unsigned SchedulingAlgorithm::rateMonotonic(Process process, [[maybe_unused]] unsigned const clock)
{
    return process.period;
}

unsigned SchedulingAlgorithm::deadlineMonotonic(Process process, [[maybe_unused]] unsigned const clock)
{
    return process.relativeDeadline;
}

unsigned SchedulingAlgorithm::earliestDeadlineFirst(Process process, unsigned const clock)
{
    return clock + process.relativeDeadline;
}

