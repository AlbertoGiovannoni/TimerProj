//
// Created by alberto on 08/03/21.
//

#include "Timer.h"
#include <cmath>

using namespace std;
using namespace std::chrono;

const int Timer::secInDay = 24*60*60;

Timer::Timer() {
    start = steady_clock::now();
    duration = ::duration<int>::zero();
    running = false;

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
            duration = ::duration <int, milli> (seconds * 1000);
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