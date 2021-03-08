cmake_minimum_required(VERSION 3.17)
project(timerlab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(timerlab
        Timer.cpp
        Timer.h)
