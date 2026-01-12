cmake_minimum_required(VERSION 4.0)

add_executable(assignment3)

target_sources(assignment3 PRIVATE
    main.cpp
    scheduler.cpp
    schedulerDemo.cpp
)

target_compile_options(assignment3 PRIVATE
    -O0
    -g3
    -fsanitize=address
    -fsanitize=undefined
)

target_link_options(assignment3 PRIVATE
    -fsanitize=address
    -fsanitize=undefined
)

