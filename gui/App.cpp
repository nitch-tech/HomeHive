//
// Created by dave on 12/03/23.
//

#include "App.h"
#include "string"
#include "HomeView.h"

/**
 * @brief Application ID for GTK
 * @details This is the application ID for GTK, used to identify the app
 * @author David Tkachuk
 */
const std::string APPLICATION_ID = "ca.uwo.cs3307.homehive";

/**
 * Retrieve the status of the application
 * @brief Retrieve the status of the application
 * @return The status of the application
 * @author David Tkachuk
 */
int App::GetStatus() {
	return this->status;
}

/**
 * Starts the GTK Application, setups up the important windowing stuff, and then opens
 * the window. Also initializes the GSettings instance.
 * @brief Starts the GTK Application
 * @param argc The number of CLI arguments
 * @param argv Array of string CLI arguments
 * @author David Tkachuk
 */
void App::Start(int argc, char** argv) {
	this->app = gtk_application_new(APPLICATION_ID.c_str(), G_APPLICATION_FLAGS_NONE);
	g_signal_connect(this->app, "activate", G_CALLBACK(App::OnActivate), (gpointer) this);

	this->settings = g_settings_new(APPLICATION_ID.c_str());

	this->status = g_application_run(G_APPLICATION(this->app), argc, argv);
	g_object_unref(this->app);
}

/**
 * Create a new window instance for the HomeHive app, and then renders all its components.
 * @brief Create the GTK Window
 * @author David Tkachuk
 */
void App::CreateWindow() {
	GtkWindow* window;
	this->window = gtk_application_window_new(this->app);
	window = GTK_WINDOW(this->window);

	gtk_window_set_application(window, this->app);
	gtk_window_set_title(window, "HOMEHIVE");
	gtk_window_set_position(window, GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_resizable(window, TRUE);
	gtk_window_set_default_size(window, 800, 600);
	gtk_window_set_default_icon_from_file("resources/icon.png", NULL);

	gtk_window_maximize(window);

	gtk_widget_show_all(this->window);

	this->view = new HomeView(window, this->settings);
	this->view->setup();
	this->view->show();
	this->event->SettingsEvent::getInstance();
	HomeView* home = dynamic_cast<HomeView*>(this->view);
	this->event->subscribe(home);

	gtk_widget_show_all(this->window);

	// auto fullscreen -
	((HomeView*) this->view)->setFullscreen(true);
}

/**
 * Application activation handler, which is called whenever the app is runned, and
 * just creates a new window.
 * @brief Application activation handler
 * @param app The GTK Application instance
 * @param data The HomeHive core App instance
 * @author David Tkachuk
 */
const void App::OnActivate(GtkApplication *app, App *data) {
	data->CreateWindow();
}

/**
 * Retrieve the GSettings instance to be able to access GTK settings options
 * @brief Retrieve GSettings instance
 * @return The GSettings instances
 * @author David Tkachuk
 */
GSettings* App::getSettings() {
	return this->settings;
}
