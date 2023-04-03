//
// Created by dave on 03/04/23.
//

#include "GreetingComponent.h"
#include "../GuiHelpers.h"

GreetingComponent::GreetingComponent() {
}

GreetingComponent::~GreetingComponent() {
}

void GreetingComponent::setup() {
	GtkWidget* innerContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	this->container = (GtkBox*) gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// create the greeting label
	GtkWidget* greeting = gtk_label_new_with_mnemonic(this->getGreetingMessage());
	this->lblGreeting = (GtkLabel*) greeting;
	addClass(greeting, "lblGreeting");
	gtk_misc_set_alignment(GTK_MISC(greeting), 1.0, 0.0);
	gtk_box_pack_start(GTK_BOX(innerContainer), greeting, true, true, 0);

	// create the settings button
	this->btnSettings = gtk_button_new();
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file ("resources/icons/gears-solid.png", NULL);// get gray icon for button
	GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 50, 50, GDK_INTERP_BILINEAR);// make it not huge
	GtkWidget *image = gtk_image_new_from_pixbuf (scaled_pixbuf);

	gtk_widget_set_size_request (btnSettings, 60, 50);
	gtk_button_set_image (GTK_BUTTON (btnSettings), image);
//	g_signal_connect(G_OBJECT(btnSettings), "clicked", G_CALLBACK(&HomeView::clickedSettings), NULL);
	//gtk_misc_set_alignment(GTK_MISC(btnSettings), 0.5, 0.5);
	gtk_box_pack_end(GTK_BOX(innerContainer), btnSettings, false, false, 10);
	addClass(btnSettings, "settingsButton");

	gtk_box_pack_start(this->container, innerContainer, false, false, 0);
}

void GreetingComponent::show() {
	gtk_grid_attach(this->parentGrid, (GtkWidget*) this->container, 2, 0, 2, 1);
}

void GreetingComponent::hide() {
}

gchar* GreetingComponent::getGreetingMessage() {
	//get preset value from Gsettings
//	const gchar* name = g_settings_get_string(settings, "name");
	gchar* greeting = g_strdup_printf("Howdy, %s!", "eee");
	return greeting;
}
