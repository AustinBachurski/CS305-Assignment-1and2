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
    // Using declaration to easily describe a function object.
    using SchedulerAlgorithm = std::function<unsigned(Process const, unsigned const)>;

    // Constructor for the Scheduler object.
    explicit Scheduler(SchedulerAlgorithm schedulingAlgorithm, unsigned &clock);

    // Calculates priority and adds the process to the CPU priority queue.
    void queueProcess(Process process);

    // Prints information about the scheduling run and the processes that were queued.
    void report();

    // Set the service time for processes.
    void setServiceTime(unsigned const time);

    // Move forward in "time" by one tick.
    bool tick();

private:

    // Variable for storing the selected scheduling algorithm.
    SchedulerAlgorithm algorithm;

    // Variable for storing the current "time".
    unsigned &clock;

    // Variable for storing the process that is currently executing.
    Process currentProcess{};

    // Priorty queue that holds processes to be executed, sorted by priority.
    std::priority_queue<Process, std::deque<Process>, ProcessPriorityComparitor> processQueue;

    // Variable for storing the service time for processes.
    unsigned serviceTime{};

    // Tracking information for each process:
    // - Total process time.
    // - Amount of completions.
    // - A processID of zero tracks CPU idle time.
    std::map<Process, ProcessData, ProcessMapComparitor> tracking;
};

#endif

