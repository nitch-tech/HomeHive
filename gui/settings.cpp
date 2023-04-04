//
// Created by Nick on Mar 20th 
//
#include <fstream>
#include "settings.h"
#include "../event/SettingsEvent.h"





Settings* Settings::settingsptr = nullptr;
Settings::Settings() {
     this->settings= g_settings_new("ca.uwo.cs3307.homehive");
     this->back_time =  g_settings_get_int(this->settings,"back");;
     this->Open = false;
}

Settings::~Settings() {
    // ...
}

Settings* Settings::getInstance() {
    if (settingsptr == nullptr) {
        settingsptr = new Settings();
    }
    return settingsptr;
}

void Settings::on_increment_clicked(GtkButton* button, gpointer user_data) {
    Settings* set = Settings::getInstance();
    set->back_time +=15;
    gchar* inc_text = g_strdup_printf("Image duration: %d (Seconds)" , set->back_time);
    gtk_label_set_text(GTK_LABEL(set->back_label), inc_text);
}

void Settings::on_decrement_clicked(GtkButton* button, gpointer user_data) {
    Settings* set = Settings::getInstance();
    if(set->back_time > 15){
        set->back_time -=15;
    }
 
    gchar* dec_text = g_strdup_printf("Image duration: %d (Seconds)", set->back_time);
    gtk_label_set_text(GTK_LABEL(set->back_label), dec_text);
}

void Settings::save_button(GtkWidget* widget, gpointer data) {
    Settings* set = Settings::getInstance();
    //write name to settings

    // Get the text from the entry widget
    const char* name = gtk_entry_get_text(GTK_ENTRY(set->name_field));
    //const char* name = gtk_entry_get_text(GTK_ENTRY(name_field)); // Get text from text field
    if(strlen(name) >0){
        g_print("OVER ONE");
        g_settings_set_string(set->settings,"name",name);
    }
 

    // write time to settings
    g_settings_set_int(set->settings,"back",set->back_time);
    SettingsEvent* event = SettingsEvent::getInstance();
    event->update_main();

}
/**
 * Close settings widnow
 * 
 * */
void Settings::closeSettings(GtkWidget* widget, gpointer data){
    Settings* set = Settings::getInstance();
    set->Open = false;
    gtk_main_quit();
}

/**
 * Settings up settings window and widgets
 * 
 * */
void Settings::open_settings_window() {
    if(!this->Open){
    this->Open = true;


    this->back_time = g_settings_get_int(this->settings,"back");

    gtk_init(NULL, NULL);
    //settings window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(&Settings::closeSettings), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //create name label
    this->name_label = gtk_label_new("Name:");
    gtk_box_pack_start(GTK_BOX(vbox), this->name_label, FALSE, FALSE, 0);

    // create name text field
    this->name_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_field), "Enter some text here...");
    gtk_box_pack_start(GTK_BOX(vbox), this->name_field, FALSE, FALSE, 0);
 
    //create background label
    gchar* back_str = g_strdup_printf("Image duration: %d (Seconds)", this->back_time);
    this->back_label = gtk_label_new_with_mnemonic(back_str);
    gtk_box_pack_start(GTK_BOX(vbox), this->back_label, FALSE, FALSE, 0);

    // create increment button
    this->inc_button = gtk_button_new_with_label("+ (15)");
    g_signal_connect(this->inc_button, "clicked", G_CALLBACK(&Settings::on_increment_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), this->inc_button, FALSE, FALSE, 0);

    // create decrement button
    this-> dec_button = gtk_button_new_with_label("- (15)");
    g_signal_connect(this->dec_button, "clicked", G_CALLBACK(&Settings::on_decrement_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), this->dec_button, FALSE, FALSE, 0);

       // create save button
    this-> button = gtk_button_new_with_label("save");
    g_signal_connect(this->button, "clicked", G_CALLBACK(&Settings::save_button), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), this->button, TRUE, FALSE, 0);

    //start window 
    gtk_widget_show_all(window);
    gtk_main();
    }
}

int Settings::getBackgroundInterval() {
	return this->back_time;
}
