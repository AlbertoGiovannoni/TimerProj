cmake_minimum_required(VERSION 3.17)
project(timerlab)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

set(SOURCE_FILES main.cpp Timer.cpp Timer.h Clock.cpp Clock.h Display.cpp Display.h)
add_executable(timerlab main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(timerlab core)

set(CURSES_NEED_NCURSES, TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(timerlab ${CURSES_LIBRARIES})
