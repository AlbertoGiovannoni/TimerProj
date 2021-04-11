//
// Created by alberto on 11/04/21.
//

#ifndef TIMERLAB_CLOCK_H
#define TIMERLAB_CLOCK_H

#include <string>

using namespace std;

class Clock {
public:
    Clock();

    int getMode() const;
    void setMode(int m);

    string getDate() const;
    string getTime() const;

private:
    int mode;

};


#endif //TIMERLAB_CLOCK_H
