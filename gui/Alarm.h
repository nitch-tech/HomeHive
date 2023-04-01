//
// Created by mariam on 2023-03-21.
//

#ifndef HOMEHIVE_ALARM_H
#define HOMEHIVE_ALARM_H

#include <iostream>
#include <fstream>
#include <string>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <time.h>
#include <chrono>
#include <thread>




class Alarm {

public:
    Alarm();
    ~Alarm();
    int getMinute();
    int getHour();
    void setMinute(int newMin);
    void setHour(int newH);
    void setNewAlarm(GDateTime* alarm);
    GDateTime* getAlarm();

private:
    int hour;
    int minute;
    GDateTime* alarm;

};


#endif //HOMEHIVE_ALARM_H
