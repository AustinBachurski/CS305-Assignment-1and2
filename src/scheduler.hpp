#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "process.hpp"

#include <deque>
#include <functional>
#include <queue>
#include <map>


// Scheduler class that manages scheduling CPU time.
class Scheduler
{
public:
    using SchedulerAlgorithm = std::function<unsigned(Process const, unsigned const)>;
    explicit Scheduler(SchedulerAlgorithm schedulingAlgorithm, unsigned &clock);
    void queueProcess(Process process);
    void report();
    void setServiceTime(unsigned const time);
    bool tick();

private:
    SchedulerAlgorithm algorithm;
    unsigned &clock;
    Process currentProcess{};
    std::priority_queue<Process, std::deque<Process>, ProcessPriorityComparitor> processQueue;
    unsigned serviceTime{};
    std::map<Process, ProcessData, ProcessMapComparitor> tracking;
};

#endif

