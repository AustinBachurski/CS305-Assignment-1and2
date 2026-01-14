#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <compare>
#include <format>
#include <functional>
#include <vector>


struct Process
{
    unsigned processID{};
    unsigned relativeDeadline{};
    unsigned period{};
    unsigned priority{};

    auto operator<=>(Process const &other) const noexcept
    {
        return processID <=> other.processID;
    }

    bool operator==(Process const &other) const noexcept
    {
        return processID == other.processID;
    }
};

struct ProcessPriorityComparitor
{
    [[nodiscard]]
    bool operator() (Process const &left, Process const &right) const noexcept
    {
        return left.priority < right.priority;
    }
};

struct ProcessMapComparitor
{
    bool operator()(Process const &left, Process const &right) const noexcept
    {
        return left.processID < right.processID;
    }
};

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

