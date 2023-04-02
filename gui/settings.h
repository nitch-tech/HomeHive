#ifndef SETTINGS_H
#define SETTINGS_H

#include <gtk/gtk.h>

class Settings {
public:
    static Settings* getInstance();
    void on_increment_clicked(GtkButton* button, gpointer user_data);
    void on_decrement_clicked(GtkButton* button, gpointer user_data);
    void save_button(GtkWidget* widget, gpointer data);
    void closeSettings(GtkWidget* widget, gpointer data);
    void saveSettings(GtkWidget* widget, gpointer data);
    void open_settings_window();

private:
    Settings();  // Make constructor private
    ~Settings(); // Make destructor private
    static Settings* settingsptr;
    GtkWidget* back_label;
    GtkWidget* name_field;
    GtkWidget* name_label;
    GtkWidget* inc_button;
    GtkWidget* dec_button;
    GtkWidget* button;
    bool Open;
    int back_time;
    GSettings* settings;
};

#endif // SETTINGS_H