//
// Created by Alberto Giovannoni on 05/11/22.
//


#include "gtest/gtest.h"

#include "../Timer.h"
#include <thread>


TEST(TimerTest, Constructor) {
    Timer t;

    ASSERT_FALSE(t.isRunning());
    ASSERT_EQ(t.getDuration(), 0);
}

TEST(TimerTest, Duration) {
    Timer t;

    ASSERT_FALSE(t.setDuration(0));
    ASSERT_FALSE(t.setDuration(86401));

    ASSERT_TRUE(t.setDuration(10));
    ASSERT_EQ(t.getDuration(), 10);
}

TEST(TimerTest, StopTimer) {
    Timer t;

    t.setDuration(2);
    t.startTimer();
    std::this_thread::sleep_for(1s);

    ASSERT_TRUE(t.stopTimer());
    ASSERT_FALSE(t.isRunning());
    ASSERT_LT(t.getDuration(), 2);
    ASSERT_GT(t.getDuration(), 0);
    ASSERT_FALSE(t.stopTimer());
}

TEST(TimerTest, ResetTimer){
    Timer t;

    t.setDuration(5);
    t.startTimer();
    time_point<steady_clock> time1 = t.getStart();
    t.resetTimer();

    ASSERT_GT(t.getStart(), time1);
}

TEST(TimerTest, StringDuration){
    Timer t;

    t.setMode(2);
    t.setDuration(1);
    ASSERT_EQ(t.getStringDuration(), "00:00:01");
    t.setDuration(61);
    ASSERT_EQ(t.getStringDuration(), "00:01:01");
    t.setDuration(3601);
    ASSERT_EQ(t.getStringDuration(), "01:00:01");
}