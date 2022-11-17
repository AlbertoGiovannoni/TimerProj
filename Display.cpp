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
    initscr(); // avvia la modalità curses
    nodelay(stdscr,true); // serve per azzerare il delay quando viene chiamato getch()
    keypad(stdscr,true); // per poter usare i comandi da tastiera

    timer.setDuration(60);
    terminalHeight = getmaxy(stdscr);
    terminalWidth = getmaxx(stdscr);
    height = 10;
    width = 30;

    timerWin = newwin(height, width, (terminalHeight-height*2 - 2)/2, (terminalWidth - width*3 + 2)/2 + 5); // creo i box
    clockWin = newwin(height, width, (terminalHeight-height*2 - 2)/2, (terminalWidth - width*3 + 2)/2 + width +4);
    text = newwin(height*0.8, width*2, (terminalHeight-height*2 - 2)/2 + height + 2, (terminalWidth - width*3 + 2)/2 + 5);
    refresh();

    do{
        update(); // aggiornamento continuo
    } while(!stop);

    endwin();

}

void Display::update() {
    keyboard();
    erase(); // pulisce i caratteri inseriti precedentemente

    werase(timerWin);
    werase(clockWin);

    wborder(timerWin, 0, 0, 0, 0, 0, 0, 0, 0); // bordi dei box
    wborder(clockWin, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
    wborder(text, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(timerWin,2,12,"Timer"); // stampe nei box
    mvwprintw(clockWin,2,12,"Clock");


    if(timer.getDuration() == 0)
        timerTime = "DRINNN!!!";
    else
        timerTime = timer.getStringDuration();

    date = clock.getDate();
    time = clock.getTime();

    mvwprintw(timerWin, 5, (width-timerTime.length())/2, &timerTime[0]);
    mvwprintw(clockWin, 4, (width-date.length())/2, &date[0]);
    mvwprintw(clockWin, 6, (width-time.length())/2, &time[0]);

    menu();

    wrefresh(timerWin);
    wrefresh(clockWin);
    wrefresh(text);

    napms(100); // attende 100 ms a terminare
}

void Display::keyboard() {
    int ch = getch(); // prende il carattere inserito

    switch(ch){
        case 27:            //ESC KEY
            stop = true;
            break;
        case KEY_RIGHT:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 1);
            }
            break;
        case KEY_LEFT:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 1);
            }
            break;
        case '1':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 60 );
            }
            break;
        case '2':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 60);
            }
            break;
        case '3':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 3600);
            }
            break;
        case '4':
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
    mvwprintw(text, 1, 1, "AGENDA:");
    mvwprintw(text, 3, 1, "TIMER | S: start | T: stop | R: reset | W: format ");
    mvwprintw(text, 4, 1, "TIMER | ->/1/3: +1s/1m/1h | <-/2/4: -1s/1m/1h");
    mvwprintw(text, 5, 1, "CLOCK | K: format");
    mvwprintw(text, 6, 1, "ESC: exit");
    wrefresh(text);
}