//
// Created by dave on 12/03/23.
//

#include "App.h"
#include "string"
#include "HomeView.h"

const std::string APPLICATION_ID = "ca.uwo.cs3307.homehive";

App::App() {
}

App::~App() {
}

int App::GetStatus() {
	return this->status;
}

/**
 * Starts the GTK app
 *
 * Setup some GTK windowing stuff, and then open the window.
 *
 * @param argc
 * @param argv
 */
void App::Start(int argc, char** argv) {
	this->app = gtk_application_new(APPLICATION_ID.c_str(), G_APPLICATION_FLAGS_NONE);
//	g_signal_connect(this->app, "activate", G_CALLBACK(this->OnActivate), (gpointer) this);
	g_signal_connect(this->app, "activate", G_CALLBACK(App::OnActivate), (gpointer) this);

	this->status = g_application_run(G_APPLICATION(this->app), argc, argv);
	g_object_unref(this->app);
}

/**
 * Create GTK Window
 *
 * This will create the base window for the entire HomeHive app, setting
 * up some basic windowing stuff.
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

	this->view = new HomeView(window);
	this->view->setup();
	this->view->show();
	gtk_widget_show_all(this->window);

	// auto fullscreen -
//	((HomeView*) this->view)->setFullscreen(true);
}

/**
 * Application activation handler
 *
 * @param app
 * @param data
 */
const void App::OnActivate(GtkApplication *app, App *data) {
	data->CreateWindow();
}
