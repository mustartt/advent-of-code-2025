cmake_minimum_required(VERSION 3.20)

project(Advent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wunused
    -Wformat=2
    -Wcast-align
    -Wnon-virtual-dtor
    -Woverloaded-virtual
)

add_executable(day1part1 day1/main.cpp)
add_executable(day1part2 day1/main2.cpp)
add_executable(day2part1 day2/main1.cpp)
add_executable(day2part2 day2/main2.cpp)
add_executable(day4part1 day4/main1.cpp)
add_executable(day4part2 day4/main2.cpp)
add_executable(day5part1 day5/main1.cpp)
add_executable(day5part2 day5/main2.cpp)
add_executable(day6part1 day6/main1.cpp)
add_executable(day6part2 day6/main2.cpp)
