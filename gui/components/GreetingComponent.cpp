#include "GreetingComponent.h"
#include "../GuiHelpers.h"
#include "../settings.h"

GreetingComponent::GreetingComponent(GSettings* settings) {
	this->settings = settings;
}

GreetingComponent::~GreetingComponent() = default;

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
	g_signal_connect(btnSettings, "clicked", G_CALLBACK(GreetingComponent::onSettingsClicked), this);
	//gtk_misc_set_alignment(GTK_MISC(btnSettings), 0.5, 0.5);
	gtk_box_pack_end(GTK_BOX(innerContainer), btnSettings, false, false, 10);
	addClass(btnSettings, "settingsButton");

	gtk_box_pack_start(this->container, innerContainer, false, false, 0);
}

void GreetingComponent::show() {
	gtk_grid_attach(this->parentGrid, (GtkWidget*) this->container, 2, 0, 2, 1);
}

/**
 * Update the component
 *
 * When executed, and if required, this component may update or re-render
 * itself to reflect any changes in the application settings.
 */
void GreetingComponent::settingsUpdated() {
	gtk_label_set_text(this->lblGreeting, this->getGreetingMessage());
}

gchar* GreetingComponent::getGreetingMessage() {
	//get preset value from Gsettings
	const gchar* name = g_settings_get_string(settings, "name");
	gchar* greeting = g_strdup_printf("Howdy, %s!", name);
	return greeting;
}

void GreetingComponent::onSettingsClicked(GtkWidget *widget, gpointer data) {
	g_print("Settings button clicked");
	Settings::getInstance()->open_settings_window();
}
