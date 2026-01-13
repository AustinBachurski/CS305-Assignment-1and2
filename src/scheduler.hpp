#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "process.hpp"

#include <deque>
#include <functional>
#include <queue>
#include <unordered_map>


// Scheduler class that manages scheduling CPU time.
class Scheduler
{
public:
    using SchedulingAlgorithm = std::function<unsigned(Process const, unsigned const)>;
    explicit Scheduler(SchedulingAlgorithm schedulingAlgorithm, unsigned &clock);
    void queueProcess(Process process);
    void report();
    void setServiceTime(unsigned const time);
    bool tick();

private:
    SchedulingAlgorithm algorithm;
    unsigned &clock;
    Process currentProcess{};
    std::priority_queue<Process, std::deque<Process>, ProcessComparitor> processQueue;
    unsigned serviceTime{};
    std::unordered_map<unsigned, ProcessData> tracking;
};

#endif

