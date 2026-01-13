#ifndef SCHEDULING_ALGORITHMS_HPP
#define SCHEDULING_ALGORITHMS_HPP

#include "process.hpp"


namespace SchedulingAlgorithm
{

unsigned rateMonotonic(Process process, [[maybe_unused]] unsigned const clock);
unsigned deadlineMonotonic(Process process, [[maybe_unused]] unsigned const clock);
unsigned earliestDeadlineFirst(Process process, unsigned const clock);

}  // namespace SchedulingAlgorithm

#endif

