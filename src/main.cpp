#include "process.hpp"
#include "schedulingAlgorithms.hpp"

#include <charconv>
#include <concepts>
#include <cstring>
#include <functional>
#include <print>

// Forward declaration for the `demo` function.
void demo(std::function<unsigned(Process const, unsigned const)>,
          unsigned const serviceTime, std::string_view algorithmFlag);

template<std::unsigned_integral T>
bool argvIsNumber(std::string_view argv, T& valueOut)
{
    return !(std::from_chars(argv.data(), argv.data() + argv.size(), valueOut).ec == std::errc{});
}

void printUsage()
{
    std::println("Usage: assignment1 <--algorithm> <service_time> (i.e. assignment1 --RMS 55)\nAvailable algorithms:\n\t\t--RMS\n\t\t--DMS\n\t\t--EDF");
}

int main(int argc, char **argv)   // Program entry point.
{
    unsigned serviceTime{};

    if (argc < 3 || argvIsNumber(argv[2], serviceTime))
    {
        printUsage();
    }
    else if (std::strcmp(argv[1], "--RMS") == 0)
    {
        demo(SchedulingAlgorithm::rateMonotonic, serviceTime, argv[1]);
    }
    else if (std::strcmp(argv[1], "--DMS") == 0)
    {
        demo(SchedulingAlgorithm::deadlineMonotonic, serviceTime, argv[1]);
    }
    else if (std::strcmp(argv[1], "--EDF") == 0)
    {
        demo(SchedulingAlgorithm::earliestDeadlineFirst, serviceTime, argv[1]);
    }
    else
    {
        printUsage();
    }
}

