//
// Created by mariam on 2023-04-02.
//

/**
 * @brief header file for InternalView
 * Abstarction expected by Timer class
 * Having abstraction helps separate Timer from the GUI. The removes cyclic dependancy
 * @author Mariam Alabi
 */
#ifndef HOMEHIVE_INTERVALVIEW_H
#define HOMEHIVE_INTERVALVIEW_H

class IntervalView {
public:
    /**
     * @brief abstract method for changing background image
     */
    virtual void changeBackgroundImage();
    /**
     * @brief abstarct method for setting date and time
     * @param date
     * @param time
     */
    virtual void setDateAndTime(char* date, char* time);
    /**
     * @brief abstract method for updating weather
     */
    virtual void updateWeather();
    /**
     * @brief abstarct method for checking if an alarm is to go off
     * @return integer that determines if an alarm went off
     */
    virtual int checkAlarm();
    /**
     * @brief abstract method for checking if a button is clicked
     */
    virtual void isClicked();

};

#endif //HOMEHIVE_INTERVALVIEW_H
