//
// Created by alberto on 11/04/21.
//

#ifndef TIMERLAB_DISPLAY_H
#define TIMERLAB_DISPLAY_H

#include <ncurses.h>
#include "Timer.h"
#include "Clock.h"

class Display {
public:
    Display();

    void init();
    void update();
    void keyboard();
    void menu();

private:
    Timer timer;
    Clock clock;

    WINDOW* timerWin = nullptr;
    WINDOW* clockWin = nullptr;
    WINDOW* text = nullptr;

    string time;
    string date;
    string timerTime;

    bool stop;
    int height;
    int width;
    int terminalWidth;
    int terminalHeight;
};


#endif //TIMERLAB_DISPLAY_H
