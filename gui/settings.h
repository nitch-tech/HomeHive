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
};

#endif // SETTINGS_H