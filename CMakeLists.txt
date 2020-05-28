cmake_minimum_required(VERSION 3.16)
project(LinuxMajorProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(LinuxMajorProject main.cpp Date.cpp Date.h Manager.cpp Manager.h Schedule.cpp Schedule.h TimeCalculator.cpp TimeCalculator.h FileIO.cpp FileIO.h)