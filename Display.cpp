//
// Created by alberto on 11/04/21.
//

#include "Display.h"
#include <ncurses.h>

Display::Display() {
    clock = Clock();
    timer = Timer();
    stop = false;
    
}

void Display::init() {
    initscr();
    nodelay(stdscr,true);
    keypad(stdscr,true);

    timer.setDuration(20);
    terminalHeight = getmaxy(stdscr);
    terminalWidth = getmaxx(stdscr);
    height = 10;
    width = 30;

    timerWin = newwin(height, width, (terminalHeight-height*2 - 2)/2, (terminalWidth - width*3 + 2)/2);
    clockWin = newwin(height, width, (terminalHeight-height*2 - 2)/2, (terminalWidth - width*3 + 2)/2 + width - 1);
    text = newwin(height, width*3-2, (terminalHeight-height*2 - 2)/2 + height + 2, (terminalWidth - width*3 + 2)/2);
    refresh();

    do{
        update();
    } while(!stop);

    endwin();

}

void Display::update() {
    keyboard();
    erase();

    werase(timerWin);
    werase(clockWin);

    wborder(timerWin, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(clockWin, 0, 0, 0, 0, ACS_TTEE, ACS_TTEE, ACS_BTEE, ACS_BTEE);
    mvwprintw(timerWin,2,10,"Timer");
    mvwprintw(clockWin,0,0,"Clock");


    if(timer.getDuration() == 0)
        timerTime = "OUT OF TIME";
    else
        timerTime = timer.getStringDuration();

    date = clock.getDate();
    time = clock.getTime();

    mvwprintw(timerWin, 1, width-timerTime.length(), &timerTime[0]);
    mvwprintw(clockWin, 1, width-date.length(), &date[0]);
    mvwprintw(clockWin, 1, width-time.length(), &time[0]);

    menu();

    wrefresh(timerWin);
    wrefresh(clockWin);
    wrefresh(text);

    napms(100);
}

void Display::keyboard() {
    int ch = getch();

    switch(ch){
        case 27:            //ESC KEY
            stop = true;
            break;
        case KEY_UP:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 1);
            }
            break;
        case KEY_DOWN:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 1);
            }
            break;
        case '1':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 10);
            }
            break;
        case '2':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 10);
            }
            break;
        case '6':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 60 );
            }
            break;
        case '7':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 60);
            }
            break;
        case '9':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 3600);
            }
            break;
        case '0':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 3600);
            }
            break;
        case 's':
                timer.startTimer();
            break;
        case 't':
            timer.stopTimer();
            break;
        case 'r':
            timer.resetTimer();
            break;
        case 'w':
            timer.setMode(timer.getMode()+1);
            break;
        case 'k':
            clock.setMode(clock.getMode()+1);
            break;
        default:
            break;
    }
}

void Display::menu() {
    mvwprintw(text, 0, 1, "TIMER | S : start, T : stop, R : reset, W : view, UP : +1s, DOWN : -1s");
    mvwprintw(text, 1, 1, "CLOCK | K : change view");
    mvwprintw(text, 4, 1, "ESC : exit");
    wrefresh(text);
}