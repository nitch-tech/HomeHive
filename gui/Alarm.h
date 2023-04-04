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
    /**
     * @brief get the minute of the alarm object
     * @return minute of alarm object
     */
    int getMinute();
    /**
     * @brief get the hour of the alarm object
     * @return
     */
    int getHour();
    /**
     * @brief set the minute of the alarm object
     * @param newMin
     */
    void setMinute(int newMin);
    /**
     * @brif set the hour of the alarm object
     * @param newH
     */
    void setHour(int newH);
    /**
     * @brief set the date of the alarm object
     *
     * When user presses 'set alarm' the date and time that was selected on the calender widget is extracted into a GDateTime* object
     * @param alarm
     */
    void setNewAlarm(GDateTime* alarm);
    /**
     * @brief get date of alarm
     *
     * Used to get the date (day, month and year) of an alarm
     * @return GDateTime* containing a date
     */
    GDateTime* getAlarm();

private:
    int hour; /// hour variable of alarm object
    int minute; ///minute of alarm object
    GDateTime* alarm; ///GDateTime has the date of the alarm

};


#endif //HOMEHIVE_ALARM_H
