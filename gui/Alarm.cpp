//
// Created by mariam on 2023-03-21.
//
/**
 * @breif a class representing an alarm object
 */

#include "Alarm.h"


/**
 * @brief Constructor that initializes an alarm object
 */
Alarm::Alarm() {
        minute = 0;
        hour = 0;
    }
Alarm::~Alarm() = default;

/**
 * @brief Get the minute of the alarm object
 * @return the minute variable
 */
int Alarm::getMinute() {
    return minute;
}
/**
 * @brief Get the hour of the alarm object
 * @return the hour variable
 */
int Alarm::getHour() {
    return hour;
}

/**
 * @brief Set a new minute
 * @param newMin. Set alarm to a new minute
 */
void Alarm::setMinute(int newMin) {
    minute = newMin;
}
/**
 * @brief Set a new hour
 * @param newH. Set alarm to a nee hour
 */
void Alarm::setHour(int newH) {
    hour = newH;
}
/**
 * @brief set the alarm date
 * @param alarm contains the date of the alarm
 */
void Alarm::setNewAlarm(GDateTime* alarm) {
    this->alarm = alarm;

}
/**
 *
 * @return the date of the alarm
 */
GDateTime* Alarm::getAlarm() {
    return alarm;
}





