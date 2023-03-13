#include <gtk/gtk.h>
#include "BaseView.h"

#ifndef HOMEHIVE_APP_H
#define HOMEHIVE_APP_H

class App {
	private:
		GtkWidget* window;
		GtkApplication* app;
		int status;
		BaseView* view;

	public:
		App();
		// App(int argc, char** argv); // not sure if we should store args into core app object?
		~App();

		void Start(int argc, char **argv);
		int GetStatus();
		void CreateWindow();

	private:
		void OnActivate(GtkApplication *app, gpointer data);
};

#endif //HOMEHIVE_APP_H
