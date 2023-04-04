/**
 * @file Settings.h
 * @author Nick
 * @brief Defines the Settings class which manages application settings.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <gtk/gtk.h>

/**
 * @class Settings
 *
 * @brief Manages application settings.
 */
class Settings {
public:
    /**
     * @brief Returns a pointer to the Settings instance.
     *
     * @return Pointer to the Settings instance.
     */
    static Settings* getInstance();
    /**
     * @brief Returns the background interval.
     *
     * @return The background interval.
     */
		int getBackgroundInterval();
    /**
     * @brief Callback function for increment button click.
     *
     * @param button The button that was clicked.
     * @param user_data User-defined data.
     */
    void on_increment_clicked(GtkButton* button, gpointer user_data);
        /**
     * @brief Callback function for decrement button click.
     *
     * @param button The button that was clicked.
     * @param user_data User-defined data.
     */
    void on_decrement_clicked(GtkButton* button, gpointer user_data);
        /**
     * @brief Saves the settings to the configuration file.
     *
     * @param widget The widget that triggered the signal.
     * @param data User-defined data.
     */
    void save_button(GtkWidget* widget, gpointer data);
        /**
     * @brief Closes the settings window.
     *
     * @param widget The widget that triggered the signal.
     * @param data User-defined data.
     */
    void closeSettings(GtkWidget* widget, gpointer data);
    
    /**
     * @brief Saves the settings and closes the settings window.
     *
     * @param widget The widget that triggered the signal.
     * @param data User-defined data.
     */
    void saveSettings(GtkWidget* widget, gpointer data);
    
    /**
     * @brief Opens the settings window.
     */
    void open_settings_window();

private:
    /**
     * @brief Private constructor to prevent creation of Settings instances.
     */
    Settings();

    /**
     * @brief Private destructor to prevent destruction of Settings instances.
     */
    ~Settings();
    static Settings* settingsptr; /**< Pointer to the Settings instance. */
    GtkWidget* back_label; /**< Label widget for the background setting. */
    GtkWidget* name_field; /**< Entry widget for the user name setting. */
    GtkWidget* name_label; /**< Label widget for the user name setting. */
    GtkWidget* inc_button; /**< Button widget for incrementing the counter. */
    GtkWidget* dec_button; /**< Button widget for decrementing the counter. */
    GtkWidget* button; /**< Button widget for saving the settings. */
    bool Open; /**< Flag to indicate whether the settings window is open or not. */
    int back_time; /**< The time in seconds for the background to change. */
    GSettings* settings; /**< The GSettings object for storing the settings. */
};

#endif // SETTINGS_H