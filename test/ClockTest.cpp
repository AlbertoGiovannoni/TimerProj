//
// Created by Alberto Giovannoni on 06/11/22.
//

#include "gtest/gtest.h"
#include "../Clock.h"

TEST(ClockTest, Constructor){
    Clock c;

    ASSERT_EQ(c.getMode(), 1);
    c.setMode(2);
    ASSERT_EQ(c.getMode(), 2);
}

TEST(ClockTest, Date){
    Clock c;
    string oldDate = "2021/01/01";
    string date = c.getDate();
    string futureDate = "3000/01/01";

    oldDate.erase(remove(oldDate.begin(), oldDate.end(), '/'));
    date.erase(remove(date.begin(), date.end(), '/'));
    futureDate.erase(remove(futureDate.begin(), futureDate.end(), '/'));

    ASSERT_GT(date, oldDate);
    ASSERT_LT(date, futureDate);
}
