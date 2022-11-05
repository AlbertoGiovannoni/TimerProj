//
// Created by alberto on 08/03/21.
//

#include "Timer.h"
#include <cmath>
#include <string>

using namespace std;
using namespace std::chrono;

const int Timer::secInDay = 86400;
const int Timer::secInHour = 3600;
const int Timer::secInMin = 60;

Timer::Timer() {
    start = steady_clock::now();
    duration = ::duration<int>::zero();
    running = false;
    mode = 1;

}

const time_point<steady_clock> &Timer::getStart() const{
    return start;
}

int Timer::getDuration() {
    if(!running) {
        return (int)round(duration.count()/1000);
    }
    else{
        time_point<steady_clock> now = steady_clock::now();
        float r = ((duration - duration_cast<milliseconds>(now-start)).count()/1000.f);
        int remaining = (int)ceil(r);
        if (remaining < 0){
            remaining = 0;
        }
        return remaining;
    }
}

bool Timer::setDuration(const unsigned int seconds) {
    if(!running) {
        if(seconds > 0 && seconds <= secInDay){
            duration = ::duration<int, milli>(seconds * 1000);
            return true;
        }
        return false;
    }
}

bool Timer::startTimer() {
    if(duration != ::duration<int>::zero()){
        if(!running){
            start = steady_clock::now();
            running = true;
            return true;
        }
        return false;
    }
}

bool Timer::stopTimer(){
    if(running){
        running = false;
        time_point<steady_clock> now = steady_clock::now();
        ::duration<int, milli> remaining = duration - duration_cast<seconds>(now - start);
        if(remaining.count() > 0){
            duration = remaining;
            return true;
        }
        return false;
    }
    return false;
}

void Timer::resetTimer() {
    start = steady_clock::now();
}

bool Timer::isRunning() const {
    return running;
}

int Timer::getMode() {
    return mode;
}

void Timer::setMode(int m) {
    mode = m%3;
}

string Timer::getStringDuration() {
    int hours;
    int min;
    int sec;
    string s;
    string tmp;

    sec = getDuration();
    hours = (int) floor(sec/secInHour);
    min = (sec - hours*secInHour) / secInMin;
    sec = sec - hours*secInHour - min*secInMin;

    switch(mode){
        case 1:
            if(hours != 0)
                s = s + to_string(hours) + " h ";
            if(hours != 0 || min != 0)
                s = s + to_string(min) + " m ";
            s = s + to_string(sec) + " s";
            break;

        case 2:
            s = (to_string(hours).length() == 1 ? ('0'+to_string(hours)) : to_string(hours)) + ":";
            s += ((tmp = to_string(min)).length() == 2) ? tmp+":" : "0"+tmp+":";
            s += ((tmp = to_string(sec)).length() == 2) ? tmp : "0"+tmp;
            break;

        default:
            s = to_string(getDuration()) + " s";
    }
    return s;
}