cmake_minimum_required(VERSION 3.14)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp TimerTest.cpp ClockTest.cpp)
add_executable(runAllTests ${TEST_SOURCE_FILES} TimerTest.cpp ClockTest.cpp)
target_link_libraries(runAllTests gtest gtest_main core)

