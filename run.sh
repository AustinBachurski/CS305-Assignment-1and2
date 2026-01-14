#!/bin/bash

# Create build directory and configure cmake if `build` does not exist.
if [[ ! -d build ]]; then
    cmake -B build
fi

# Build project.
cmake --build build

# Run project for each algorithm, outputting to file.
./build/bin/assignment3 --RMS 15 > output/Rate-Monotonic.txt
./build/bin/assignment3 --DMS 15 > output/Deadline-Monotonic.txt
./build/bin/assignment3 --EDF 15 > output/Earliest-Deadline-First.txt

# Status code, info dump, and exit.
echo "Program exited with code $?.  Output written to 'output' directory."

