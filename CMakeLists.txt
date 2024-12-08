cmake_minimum_required(VERSION 3.10)
project(Xylonet CXX)

# Set C++ standard to 17 (or 20, depending on your compiler)
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(src)

# Add source files and create executable
add_executable(xylonet main.cpp src/transaction.h)
