//
// Created by alberto on 11/04/21.
//

#include "Clock.h"

using namespace std;

Clock::Clock() {
    mode = 2;
}
int Clock::getMode() const {
    return mode;
}

void Clock::setMode(int m) {
    mode = m;
}

string Clock::getDate() const {
    time_t now = time(0);
    tm date = *localtime(&now);
    string s;
    string tmp;

    switch(mode){
        case 1:
            s += "'" + to_string(date.tm_year%100);
            tmp = to_string(date.tm_mon+1);
            s += "/" + (tmp.length() == 1 ? ('0'+tmp) : tmp);
            tmp = to_string(date.tm_mday);
            s += "/" + (tmp.length() == 1 ? ('0'+tmp) : tmp);

            break;
        case 2:
            switch (date.tm_wday){
                case 0:
                    s += "Domenica";
                    break;
                case 1:
                    s += "Lunedì";
                    break;
                case 2:
                    s += "Martedì";
                    break;
                case 3:
                    s += "Mercoledì";
                    break;
                case 4:
                    s += "Giovedì";
                    break;
                case 5:
                    s += "Venerdì";
                    break;
                case 6:
                    s += "Sabato";
                    break;

            }
            tmp = to_string(date.tm_mday);
            s += ' ' + (tmp.length() == 1 ? ('0'+tmp) : tmp) + ' ';
            switch (date.tm_mon){
                case 0:
                    s += "Gennaio";
                    break;
                case 1:
                    s += "Febbraio";
                    break;
                case 2:
                    s += "Marzo";
                    break;
                case 3:
                    s += "Aprile";
                    break;
                case 4:
                    s += "Maggio";
                    break;
                case 5:
                    s += "Giugno";
                    break;
                case 6:
                    s += "Luglio";
                    break;
                case 7:
                    s += "Agosto";
                    break;
                case 8:
                    s += "Settembre";
                    break;
                case 9:
                    s += "Ottobre";
                    break;
                case 10:
                    s += "Novembre";
                    break;
                case 11:
                    s += "Dicembre";
                    break;
            }
            s += ' ' + to_string(1900 + date.tm_year);
            break;
        default:
            tmp = to_string(date.tm_mday);
            s += tmp.length() == 1 ? ('0'+tmp) : tmp;
            tmp = to_string(date.tm_mon+1);
            s += "/" + (tmp.length() == 1 ? ('0'+tmp) : tmp);
            s += "/'" + to_string(date.tm_year%100);
    }
    return s;
}

string Clock::getTime() const {
    time_t now = time(0);
    tm date = *localtime(&now);
    string s;
    string tmp;
    switch(mode){
        case 1:
            tmp = to_string(date.tm_hour%12);
            s += (tmp.length() == 1 ? ('0'+tmp) : tmp);
            tmp = to_string(date.tm_min);
            s += ":" + (tmp.length() == 1 ? ('0'+tmp) : tmp);
            s += date.tm_hour < 12 ? "am" : "pm";

        case 2:
            tmp = to_string(date.tm_hour);
            s += (tmp.length() == 1 ? ('0'+tmp) : tmp);
            tmp = to_string(date.tm_min);
            s += ":" + (tmp.length() == 1 ? ('0'+tmp) : tmp);
            tmp = to_string(date.tm_sec);
            s += " :" + (tmp.length() == 1 ? ('0'+tmp) : tmp);
            break;
        default:
            tmp = to_string(date.tm_hour);
            s += (tmp.length() == 1 ? ('0'+tmp) : tmp);
            tmp = to_string(date.tm_min);
            s += ":" + (tmp.length() == 1 ? ('0'+tmp) : tmp);
    }
    return s;
}




