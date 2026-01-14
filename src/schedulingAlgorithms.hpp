#ifndef SCHEDULING_ALGORITHMS_HPP
#define SCHEDULING_ALGORITHMS_HPP

#include "process.hpp"


namespace SchedulingAlgorithm
{

// Rate Monotonic priority calculation.
unsigned rateMonotonic(Process process, [[maybe_unused]] unsigned const clock);

// Deadline First priority calculation.
unsigned deadlineMonotonic(Process process, [[maybe_unused]] unsigned const clock);

// Earliest Deadline First priority calculation.
unsigned earliestDeadlineFirst(Process process, unsigned const clock);

}  // namespace SchedulingAlgorithm

#endif

