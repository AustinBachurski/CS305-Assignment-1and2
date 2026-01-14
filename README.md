# Computer Science 305 via Study.com - Assignment 3: Development of Real-Time Scheduling Simulator

## Required Tooling

> The project expects a Linux environment, tested in Ubuntu 24.04.3 LTS via WSL and Arch.

### CMake
- *CMake is the de-facto standard for building C++ code.* - [CMake.org](https://cmake.org/)
- Tested with version 4.2.1

### GCC
- *The GNU Compiler Collection includes front ends for C, C++, Objective-C, Fortran, Ada, Go, D, Modula-2, and COBOL as well as libraries for these languages (libstdc++,...).* - [gcc.gnu.org](https://gcc.gnu.org/)
- Tested with version 15.2

## Build Instructions

> Build and run automatically.
1. Clone the repository.
1. Run the build script: `./run.sh`

> Build and run manually. 
1. Clone the repository.
1. Create a build directory: `cmake -B build`
1. Build the project: `cmake --build build`
1. Run the application with the appropriate flags: `./build/bin/assignment3 <--algorithm_flag> <service_time>`

#### Flags

- `--RMS` *- Rate Monotonic Scheduler*
- `--DMS` *- Deadline Monotonic Scheduler*
- `--EDF` *- Earliest Deadline First Scheduler*
- Following the algorithm flag, include the Service Time for each process as an integral value.
> Usage example: `./build/bin/assignment3 --RMS 15`

## Output

When running with the included `run.sh` shell script, the program will be executed and the output will be saved to a `.txt` file in the `output` directory for each algorithm.

![Demo of running jobs.](screenshots/demo.png)

