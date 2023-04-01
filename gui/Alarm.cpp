//
// Created by mariam on 2023-03-21.
//


#include "Alarm.h"

    Alarm::Alarm() {
        minute = 0;
        hour = 0;


    }
Alarm::~Alarm() = default;

int Alarm::getMinute() {
    return minute;
}
int Alarm::getHour() {
    return hour;
}

void Alarm::setMinute(int newMin) {
    minute = newMin;
}
void Alarm::setHour(int newH) {
    hour = newH;
}

void Alarm::setNewAlarm(GDateTime* alarm) {
    this->alarm = alarm;

}
GDateTime* Alarm::getAlarm() {
    return alarm;

}





