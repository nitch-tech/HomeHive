//
// Created by mariam on 2023-04-02.
//

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
