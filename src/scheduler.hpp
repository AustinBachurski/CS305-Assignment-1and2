#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "process.hpp"

#include <deque>
#include <functional>
#include <queue>


// Scheduler class that manages scheduling CPU time.
class Scheduler
{
public:
    using SchedulingAlgorithm = std::function<uint8_t(Process const)>;
    explicit Scheduler(SchedulingAlgorithm schedulingAlgorithm)
    : algorithm{ schedulingAlgorithm }
    {};
    void queueProcess(Process const);

private:
    Process updatePriority(Process process) const;

    SchedulingAlgorithm algorithm;
    Process currentProcess{};
    std::priority_queue<Process, std::deque<Process>, ProcessComparitor> queue;
};

#endif

