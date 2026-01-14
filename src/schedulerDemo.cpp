#include "scheduler.hpp"
#include "process.hpp"

#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>


// An annonymous namespace makes the functions within it inaccessible outside
// of this translation unit.  Basically making free functions private.
namespace
{

// Helper function that displays invalid input and exits the program.
// This is called if an input file cannot be parsed correctly.
[[noreturn]]
void invalidInput(std::string_view const line)
{
    std::println("Invalid input encountered!");
    std::println("Found: {}", line);
    std::exit(1);
}

// Helper function that parses a string to a number.
unsigned parseField(std::string_view const field, std::string_view const line)
{
    unsigned value{};

    if (!(std::from_chars(field.data(), field.data() + field.size(), value).ec == std::errc{}))
    {
        invalidInput(line);
    }

    return value;
}

// Helper function to create a Process object from the CSV input.
Process makeProcess(std::string_view const line)
{
    auto fields = line | std::views::split(',')
                       | std::views::transform([](auto&& split_view)
                             { return std::string_view{ split_view }; });

    Process process;

    auto fieldsIter{ fields.begin() };

    auto nextField{ [&fieldsIter, &fields, line]()
    {
        if (fieldsIter == fields.end()) { invalidInput(line); }
        return *fieldsIter++;
    }};

    process.processID = parseField(nextField(), line);
    process.relativeDeadline = parseField(nextField(), line);
    process.period = parseField(nextField(), line);

    return process;
}

// Helper function that creates a vector of Process objects by reading data from an input file.
std::vector<Process> getProcessesFromFile(std::filesystem::path filePath)
{
    std::vector<Process> processes;

    if (!std::filesystem::exists(filePath))
    {
        std::println("Input file not found: {}!", filePath.string());
        std::exit(1);
    }

    std::ifstream file{ filePath };

    if (!file.is_open())
    {
        std::println("Failed to open input file: {}!", filePath.string());
        std::exit(1);
    }

    std::string line;

    std::getline(file, line);  // Skip csv header.

    while (std::getline(file, line))
    {
        processes.push_back(makeProcess(line));
    }

    return processes;
}

// Queue all processes at time zero.
void preloadProcesses(std::span<Process const> processes, Scheduler &scheduler)
{
    for (auto const& process : processes)
    {
        scheduler.queueProcess(process);
    }
}

// Select the next process to be queued based on the current time and the process period.
Process soonestPeriodProcess(std::span<Process const> processes, unsigned const clock)
{
    return *std::ranges::min_element(processes, [clock](Process const& left, Process const& right)
             {
                return clock % left.period <= clock % right.period;
             });;
}

// Convert the algorithm flag to the algorithm name for reporting.
std::string_view algorithmName(std::string_view algorithmFlag)
{
    if (algorithmFlag == "--RMS")
    {
        return "Rate Monotonic";
    }
    else if (algorithmFlag == "--DMS")
    {
        return "Deadline Monotonic";
    }
    else if (algorithmFlag == "--EDF")
    {
        return "Earliest Deadline First";
    }

    throw std::invalid_argument('<' + std::string{ algorithmFlag } + "> is not a valid flag.");
}

}  // Anonymous Namespace


// Function that demonstrates memory management and operating system functionality.
void demo(std::function<unsigned(Process const, unsigned const)> algorithm,
          unsigned const serviceTime, std::string_view algorithmFlag)
{
    constexpr unsigned maximumRunTime{ 3000 };
    unsigned clock{};
    Scheduler scheduler(algorithm, clock);
    scheduler.setServiceTime(serviceTime);

    std::vector<Process> processes{ getProcessesFromFile("data/input.csv") };
    preloadProcesses(processes, scheduler);

    while (scheduler.tick() && clock < maximumRunTime)
    {
        if (Process next{ soonestPeriodProcess(processes, clock) }; clock % next.period == 0)
        {
            scheduler.queueProcess(next);
        }
    }

    std::println("Scheduler Report for {} scheduler with process service time of {}.", algorithmName(algorithmFlag), serviceTime);
    scheduler.report();
}

