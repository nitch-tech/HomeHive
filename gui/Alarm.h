//
// Created by mariam on 2023-03-21.
//
/**
 * When a user sets an alarm, information about the alarm is stored in the alarm class
 * @author Mariam Alabi
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
     * @author Mariam Alabi
     */
    Alarm();
    /**
    * @brief deconstructor for alarm class
     * @author Mariam Alabi
    */
    ~Alarm();
    /**
     * @brief get the minute of the alarm object
     * @return minute of alarm object
     * @author Mariam Alabi
     */
    int getMinute();
    /**
     * @brief get the hour of the alarm object
     * @return the hour as an integer
     * @author Mariam Alabi
     */
    int getHour();
    /**
     * @brief set the minute of the alarm object
     *
     * If a user wants to set an alarm, this function sets the minute of the alarm
     * @param newMin the new minute of the alarm
     * @author Mariam Alabi
     */
    void setMinute(int newMin);
    /**
     * @brif set the hour of the alarm object
     *
     * If a user wants to set an alarm, this function sets the hour of the alarm
     * @param newH the new hour of the alarm
     * @author Mariam Alabi
     */
    void setHour(int newH);
    /**
     * @brief set the date of the alarm object
     *
     * When user presses 'set alarm' the date and time that was selected on the calender widget is extracted into a GDateTime* object
     * @param alarm has the date of the alarm
     *
     * @author Mariam Alabi
     */
    void setNewAlarm(GDateTime* alarm);
    /**
     * @brief get date of alarm
     *
     * Used to get the date (day, month and year) of an alarm
     * @return GDateTime* containing a date
     * @author Mariam Alabi
     */
    GDateTime* getAlarm();

private:
    int hour; /// hour variable of alarm object
    int minute; ///minute of alarm object
    GDateTime* alarm; ///GDateTime has the date of the alarm

};


#endif //HOMEHIVE_ALARM_H
