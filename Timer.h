//
// Created by alberto on 08/03/21.
//

#ifndef TIMERLAB_TIMER_H
#define TIMERLAB_TIMER_H

#include "chrono"
#include <string>


using namespace std;
using namespace std::chrono;

class Timer {
public:
    Timer();

        const time_point<steady_clock> &getStart() const;

        int getDuration();
        bool setDuration(unsigned int seconds);

        bool startTimer();
        bool stopTimer();
        void resetTimer();

        bool isRunning() const;

        string getStringDuration();
        int getMode();
        void setMode(int m);


private:
    bool running;
    time_point<steady_clock> start;
    ::duration<int, milli> duration;

    int mode;

    static const int secInDay;
    static const int secInHour;
    static const int secInMin;
};


#endif //TIMERLAB_TIMER_H
