#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <compare>
#include <format>
#include <vector>


// Process object representing a task for the CPU to perform.
struct Process
{
    unsigned processID{};
    unsigned runTime{};
    unsigned relativeDeadline{};
    unsigned period{};
    unsigned priority{};

    // Provides comparison functions based on the processID field.
    auto operator<=>(Process const &other) const noexcept
    {
        return processID <=> other.processID;
    }

    // Spaceship operator `<=>` only produces strong ordering if all fields
    // are used.  So we have to explicitly define equality.
    bool operator==(Process const &other) const noexcept
    {
        return processID == other.processID;
    }
};

// This functor is used by the scheduler's priority queue to sort Process objects.
struct ProcessPriorityComparitor
{
    [[nodiscard]]
    bool operator() (Process const &left, Process const &right) const noexcept
    {
        return left.priority < right.priority;
    }
};

// This functor is used by the tracking map to sort Process objects.
struct ProcessMapComparitor
{
    bool operator()(Process const &left, Process const &right) const noexcept
    {
        return left.processID < right.processID;
    }
};

// This struct holds the tracking information for a process.
struct ProcessData
{
    std::size_t executionTime{};
    std::vector<unsigned> completionTimes;
};

// The std::formatter object is required by the std::print and std::println functions ot the 
// C++ Standard Template Library.  It defines how the object will be printed.
// In this case, it is the Process object.
template<>
struct std::formatter<Process>
{
    // `parse` defines behavior for format strings, unnecessary for this object.
    constexpr auto parse(std::format_parse_context& context)
    {
        return context.begin();
    }

    // `format` defines the output that will be printed by std::print/std::println
    auto format(Process const &process, std::format_context &context) const
    {
        return std::format_to(context.out(), "Process {}: Period-{}, ", process.processID, process.period);
    }
};

// The std::formatter object is required by the std::print and std::println functions ot the 
// C++ Standard Template Library.  It defines how the object will be printed.
// In this case, it is the ProcessData object.
template<>
struct std::formatter<ProcessData>
{
    // `parse` defines behavior for format strings, unnecessary for this object.
    constexpr auto parse(std::format_parse_context& context)
    {
        return context.begin();
    }

    // `format` defines the output that will be printed by std::print/std::println
    auto format(ProcessData const &data, std::format_context &context) const
    {
        return std::format_to(context.out(), "ExecutionTime-{}, CompletionTimes-{}", data.executionTime, data.completionTimes);
    }
};

#endif

