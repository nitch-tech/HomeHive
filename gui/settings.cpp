#include <gtk/gtk.h>


static int count = 0;
static void inc_button_clicked(GtkWidget *widget, gpointer data)
{
    count++;
    char buffer[10];
    sprintf(buffer, "%d", count);
    gtk_label_set_text(GTK_LABEL(data), buffer);
}

static void dec_button_clicked(GtkWidget *widget, gpointer data)
{
    count--;
    char buffer[10];
    sprintf(buffer, "%d", count);
    gtk_label_set_text(GTK_LABEL(data), buffer);
}

void open_settings_window() {

  
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *name_label = gtk_label_new("Name:");
    gtk_box_pack_start(GTK_BOX(vbox), name_label, FALSE, FALSE, 0);

    GtkWidget *name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), name_entry, FALSE, FALSE, 0);

    GtkWidget *count_label = gtk_label_new("Count: 0");
    gtk_box_pack_start(GTK_BOX(vbox), count_label, FALSE, FALSE, 0);

    GtkWidget *inc_button = gtk_button_new_with_label("+");
    g_signal_connect(inc_button, "clicked", G_CALLBACK(inc_button_clicked), count_label);
    gtk_box_pack_start(GTK_BOX(vbox), inc_button, FALSE, FALSE, 0);

    GtkWidget *dec_button = gtk_button_new_with_label("-");
    g_signal_connect(dec_button, "clicked", G_CALLBACK(dec_button_clicked), count_label);
    gtk_box_pack_start(GTK_BOX(vbox), dec_button, FALSE, FALSE, 0);

    GtkWidget *email_label = gtk_label_new("Email:");
    gtk_box_pack_start(GTK_BOX(vbox), email_label, FALSE, FALSE, 0);

    GtkWidget *email_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), email_entry, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}