#include "scheduler.hpp"
#include "process.hpp"

#include <functional>
#include <print>


Scheduler::Scheduler(SchedulerAlgorithm schedulingAlgorithm, unsigned &systemClock)
: algorithm{ schedulingAlgorithm }
, clock{ systemClock }
{};

void Scheduler::queueProcess(Process process)
{
    process.priority = std::invoke(algorithm, process, clock);
    process.relativeDeadline = clock + process.relativeDeadline;

    if (!currentProcess.processID)
    {
        currentProcess = process;
    }
    else if (process.priority < currentProcess.priority)
    {
        processQueue.push(currentProcess);
        currentProcess = process;
    }
    else
    {
        processQueue.push(process);
    }
}

void Scheduler::report()
{
    if (currentProcess.relativeDeadline < clock)
    {
        std::println("**Schedule is feasible from 0 to {} when process {} did not meet it's deadline.**", clock, currentProcess.processID);
    }
    else
    {
        std::println("**Schedule is feasible from 0 to {} without failure.**", clock);
    }

    for (auto const& [process, processData] : tracking)
    {
         std::println("- {}{}", process, processData);
    }
}

void Scheduler::setServiceTime(unsigned const time)
{
    serviceTime = time;
}

bool Scheduler::tick()
{
    // Increment the current clock and the run time tracking for the current process.
    // If processID is zero, we're tracking idle time.
    ++clock;
    ++tracking[currentProcess].executionTime;

    // CPU is idle.
    if (!currentProcess.processID)
    {
        return true;
    }

    // Process missed deadline.
    if (currentProcess.relativeDeadline < clock)
    {
        return false;
    }


    // Process complete.
    if (tracking[currentProcess].executionTime == serviceTime)
    {
        tracking[currentProcess].completionTimes.push_back(clock);

        if (!processQueue.empty())
        {
            currentProcess = processQueue.top();
            processQueue.pop();
        }
        else
        {
            currentProcess = {};
        }
    }

    // Current process is either running, or CPU is idling.
    return true;
}

