#include <gtk/gtk.h>
#include "BaseView.h"
#include "../event/SettingsEvent.h"
#ifndef HOMEHIVE_APP_H
#define HOMEHIVE_APP_H

class App {
	private:
		GtkWidget* window;
		GtkApplication* app;
		int status;
		BaseView* view;

		GSettings* settings;
		SettingsEvent* event;

	public:
		App();
		// App(int argc, char** argv); // not sure if we should store args into core app object?
		~App();

		GSettings* getSettings();

		void Start(int argc, char **argv);
		int GetStatus();
		void CreateWindow();

		static const void OnActivate(GtkApplication *app, App* data);
};

#endif //HOMEHIVE_APP_H
