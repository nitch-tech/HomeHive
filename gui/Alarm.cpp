//
// Created by mariam on 2023-03-21.
//


#include "Alarm.h"

    Alarm::Alarm() {


    }

    /*
GCallback on_button_clicked(GtkWidget* button, gpointer data) {
    Alarm* obj = reinterpret_cast<Alarm*>(data);
    obj->do_something();
}

void do_something() {
    g_print("Button clicked\n");
} */

    void on_button_clicked(GtkButton* button) {
        g_print("Button clicked\n");
    }

