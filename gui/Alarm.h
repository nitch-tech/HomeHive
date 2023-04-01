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
    ~Alarm() ;
    /*
    GCallback on_button_clicked(GtkWidget* button);

    void do_something(); */
    static void on_button_clicked(GtkButton* button);

    void setMinute(GtkWidget* widget, gpointer user_data);
    void on_button_clicked();
    int getMinute();
    void testMin(int minn);

    void setHour(GtkWidget* widget, gpointer user_data);

    void setNewAlarm(GDateTime* alarm);
    int getHour();
    void setMinute(int newMin);
    void setHour(int newH);
    GDateTime* getAlarm();

private:
    int hour;
    int minute;
    GDateTime* alarm;

};


#endif //HOMEHIVE_ALARM_H
