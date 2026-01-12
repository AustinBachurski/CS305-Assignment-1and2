#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>
#include <format>









// The std::formatter object is required by the std::print and std::println functions ot the 
// C++ Standard Template Library.  It defines how the object will be printed.
// In this case, it is the JobState object.
template<>
struct std::formatter<JobState>
{
    // `parse` defines behavior for format strings, unnecessary for this object.
    constexpr auto parse(std::format_parse_context& context)
    {
        return context.begin();
    }

    // `format` defines the output that will be printed by std::print/std::println
    auto format(JobState const& state, std::format_context& context) const
    {
        switch (state)
        {
            case JobState::end:
                return std::format_to(context.out(), "End");

            case JobState::queued:
                return std::format_to(context.out(), "Queued");

            case JobState::running:
            {
                return std::format_to(context.out(), "Running");
            }

            case JobState::open:
            {
                return std::format_to(context.out(), "Open");
            }

            case JobState::blocked:
                return std::format_to(context.out(), "Blocked");

            case JobState::sleeping:
                return std::format_to(context.out(), "Sleeping");
        }
        return std::format_to(context.out(), "Undefined case in formatter!");
    }
};

// The std::formatter object is required by the std::print and std::println functions ot the 
// C++ Standard Template Library.  It defines how the object will be printed.
// In this case, it is the Job object.
template<>
struct std::formatter<Job>
{
    // `parse` defines behavior for format strings, unnecessary for this object.
    constexpr auto parse(std::format_parse_context& context)
    {
        return context.begin();
    }

    // `format` defines the output that will be printed by std::print/std::println
    auto format(Job const& job, std::format_context& context) const
    {
        if (job.jobType == JobType::job)
        {
            return std::format_to(context.out(), "Job {} - {}", job.jobID, job.currentState);
        }
        else
        {
            return std::format_to(context.out(), "File {} - {}", job.jobID, job.currentState);
        }
    }
};

#endif

