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
 * Application activation handler
 *
 * Gross weird thing that GTK wants? They seem to expect an app to be static,
 * and thus need a static activation function. Which is supposed to setup
 * the basics (ie: all windows) and then add functionality.
 *
 * @param app
 * @param data
 * @todo improve this
 */
static void activate(GtkApplication *app, App* data) {
	data->CreateWindow();
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
	g_signal_connect(this->app, "activate", G_CALLBACK(activate), (gpointer) this);

	this->status = g_application_run(G_APPLICATION(this->app), argc, argv);
	g_object_unref(this->app);
}

void App::OnActivate(GtkApplication *app, gpointer data) {

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
	gtk_window_set_default_size(window, 1280, 720);
	gtk_window_set_default_icon_from_file("icon.png", NULL);

	gtk_window_maximize(window);

	gtk_widget_show_all(this->window);

	this->view = new HomeView(window);
	this->view->setup();
	this->view->show();
	gtk_widget_show_all(this->window);

	// auto fullscreen -
//	((HomeView*) this->view)->setFullscreen(true);
}
