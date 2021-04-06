//
// Created by alberto on 08/03/21.
//

#ifndef TIMERLAB_TIMER_H
#define TIMERLAB_TIMER_H
#include "chrono"

using namespace std;
using namespace std::chrono;

class Timer {
public:
    Timer();

        const time_point<steady_clock> &getStart() const;

        int getDuration();
        bool setDuration(unsigned int seconds);


private:
    bool running;
    time_point<steady_clock> start;
    ::duration<int, milli> duration;

};


#endif //TIMERLAB_TIMER_H
