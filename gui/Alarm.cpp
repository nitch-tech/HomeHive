//
// Created by mariam on 2023-03-21.
//


#include "Alarm.h"

    Alarm::Alarm() {
        minute = 0;
        hour = 0;


    }
Alarm::~Alarm() = default;

void Alarm::setMinute(GtkWidget* widget, gpointer user_data) {

    GtkWidget *button = (GtkWidget*)user_data;
    this->setMinute(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(button)));
    g_print("Button clicked on the ALARMM CLASS setMINUTE fxn %d\n", this->getMinute());

}

void Alarm::setHour(GtkWidget* widget, gpointer user_data) {

    GtkWidget *button = (GtkWidget*)user_data;
    this->setHour(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(button)));
    g_print("Button clicked on the ALARMM CLASS setHour fxn %d\n", this->getHour());

}

void Alarm::on_button_clicked() {
    printf("The button works");

}

void Alarm::testMin(int minn) {

}

int Alarm::getMinute() {
    return minute;
}
int Alarm::getHour() {
    return hour;
}

void Alarm::setMinute(int newMin) {
    minute = newMin;
    //printf("The minute is ALARM LASS %d\n", getMinute());
}
void Alarm::setHour(int newH) {
    hour = newH;
    //printf("The HOUR is ALARM LASS %d\n", getHour());
}

void Alarm::setNewAlarm(GDateTime* alarm) {
    this->alarm = alarm;

}
GDateTime* Alarm::getAlarm() {
    return alarm;

}





