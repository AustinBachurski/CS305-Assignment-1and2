#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>
#include <format>
#include <vector>


struct Process
{
    uint8_t processID{};
    uint8_t relativeDeadline{};
    uint8_t period{};
    uint8_t priority{};
};

struct ProcessComparitor
{
    [[nodiscard]]
    bool operator() (Process const left, Process const right) const
    {
        return left.priority < right.priority;
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
    auto format(Process const& process, std::format_context& context) const
    {
        return std::format_to(context.out(), "Process {}, Period-{}: ", process.processID, process.period);
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
    auto format(ProcessData const& data, std::format_context& context) const
    {
        return std::format_to(context.out(), "ExecutionTime-{}, CompletionTimes-{}", data.executionTime, data.completionTimes);
    }
};

#endif

