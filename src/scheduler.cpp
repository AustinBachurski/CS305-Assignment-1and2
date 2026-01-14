#include "scheduler.hpp"
#include "process.hpp"

#include <functional>
#include <print>

// The methods in this file are described with comments in `scheduler.hpp`.

Scheduler::Scheduler(SchedulerAlgorithm schedulingAlgorithm, unsigned &systemClock)
: algorithm{ schedulingAlgorithm }
, clock{ systemClock }
{};

void Scheduler::queueProcess(Process process)
{
    // Call the scheduling algorithm function.
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
    if (currentProcess.processID && currentProcess.relativeDeadline < clock)
    {
        std::println("- Schedule is feasible from 0 to {} when process {} did not meet it's deadline of {}.", clock, currentProcess.processID, currentProcess.relativeDeadline);
    }
    else
    {
        std::println("- Schedule is feasible from 0 to {} without failure.", clock);
    }

    std::size_t idleTime{};
    std::size_t runTime{};

    for (auto const& [process, processData] : tracking)
    {
        if (process.processID)
        {
            runTime += processData.executionTime;
            std::println("   {}{}", process, processData);
        }
        else
        {
            idleTime += processData.executionTime;
        }
    }

    std::println("- CPU Usage Time-{}, CPU Idle Time-{}\n", runTime, idleTime);
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
    ++currentProcess.runTime;
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
    if (currentProcess.runTime == serviceTime)
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

