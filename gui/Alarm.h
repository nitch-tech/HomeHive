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




class Alarm {

public:
    Alarm();
    /*
    GCallback on_button_clicked(GtkWidget* button);

    void do_something(); */
    void on_button_clicked(GtkButton* button);

};


#endif //HOMEHIVE_ALARM_H
