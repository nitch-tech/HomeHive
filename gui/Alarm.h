//
// Created by mariam on 2023-03-21.
//
/**
 * @author Mariam
 * @brief Header file for alarm class
 */

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
    /**
     * @brief constructor for alarm class
     */
    Alarm();
    /**
    * @brief deconstructor for alarm class
    */
    ~Alarm();
    int getMinute();
    int getHour();
    void setMinute(int newMin);
    void setHour(int newH);
    void setNewAlarm(GDateTime* alarm);
    GDateTime* getAlarm();

private:
    int hour; /// hour variable of alarm object
    int minute; ///minute of alarm object
    GDateTime* alarm; ///GDateTime has the date of the alarm

};


#endif //HOMEHIVE_ALARM_H
