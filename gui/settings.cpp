//
// Created by Nick on Mar 20th 
//
#include <gtk/gtk.h>
#include <fstream>
static GSettings* settings = g_settings_new("ca.uwo.cs3307.homehive");
static bool Open = false;
static int back_time = 15;
// Callback function for saving changes
GtkWidget* back_label;
void on_increment_clicked(GtkButton* button, gpointer user_data) {
    back_time +=1;
    gchar* inc_text = g_strdup_printf("Background change interval: %d", back_time);
    gtk_label_set_text(GTK_LABEL(back_label), inc_text);
}

void on_decrement_clicked(GtkButton* button, gpointer user_data) {
    back_time -=1;
    gchar* dec_text = g_strdup_printf("Background change interval: %d", back_time);
    gtk_label_set_text(GTK_LABEL(back_label), dec_text);
}

void save_button(GtkWidget* widget, gpointer data) {
    //write name to settings
    GtkWidget* name_field = (GtkWidget*) data; // Get text field widget from data pointer
    
    const char* name = gtk_entry_get_text(GTK_ENTRY(name_field)); // Get text from text field
    if(strlen(name) >0){
    g_settings_set_string(settings,"name",name);
    }
 

    // write time to settings
    g_settings_set_int(settings,"back",back_time);
}
/**
 * Close settings widnow
 * 
 * */
void closeSettings(){
    Open = false;
    gtk_main_quit();
}
/**
 * TODO 
 * send signal to update stuff in HOMEVIEW
 * 
 * */
void saveSettings() {
    // Update the label in HomeView
    
}
/**
 * Settings up settings window and widgets
 * 
 * */
void open_settings_window() {
    if(!Open){
    Open = true;


    // Parse the JSON file into a JSON object

    gtk_init(NULL, NULL);
    //settings window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(closeSettings), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //create name label
    GtkWidget *name_label = gtk_label_new("Name:");
    gtk_box_pack_start(GTK_BOX(vbox), name_label, FALSE, FALSE, 0);

    // create name text field
    GtkWidget* name_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_field), "Enter some text here...");
    gtk_box_pack_start(GTK_BOX(vbox), name_field, FALSE, FALSE, 0);
 
    //create background label
    gchar* back_str = g_strdup_printf("Background change interval: %d", back_time);
    back_label = gtk_label_new_with_mnemonic(back_str);
    gtk_box_pack_start(GTK_BOX(vbox), back_label, FALSE, FALSE, 0);

    // create increment button
    GtkWidget* inc_button = gtk_button_new_with_label("+");
    g_signal_connect(inc_button, "clicked", G_CALLBACK(on_increment_clicked), name_field);
    gtk_box_pack_start(GTK_BOX(vbox), inc_button, FALSE, FALSE, 0);

    // create decrement button
    GtkWidget* dec_button = gtk_button_new_with_label("-");
    g_signal_connect(dec_button, "clicked", G_CALLBACK(on_decrement_clicked), name_field);
    gtk_box_pack_start(GTK_BOX(vbox), dec_button, FALSE, FALSE, 0);

       // create save button
    GtkWidget* button = gtk_button_new_with_label("save");
    g_signal_connect(button, "clicked", G_CALLBACK(save_button), name_field);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    //start window 
    gtk_widget_show_all(window);
    gtk_main();
    }
}