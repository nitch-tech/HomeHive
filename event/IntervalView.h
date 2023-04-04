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
    virtual void changeBackgroundImage();
    virtual void setDateAndTime(char* date, char* time);
    virtual void updateWeather();
    virtual int checkAlarm();
    virtual void isClicked();

};

#endif //HOMEHIVE_INTERVALVIEW_H
