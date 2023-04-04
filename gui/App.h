#include <gtk/gtk.h>
#include "BaseView.h"
#include "../event/SettingsEvent.h"
#ifndef HOMEHIVE_APP_H
#define HOMEHIVE_APP_H

/**
 * The main application class, which handles the GTK application lifecycle
 * and the main window.
 * @brief The main application class
 * @author David Tkachuk
 */
class App {
	private:
		GtkWidget* window;
		GtkApplication* app;
		int status;
		BaseView* view;

		GSettings* settings;
		SettingsEvent* event;

	public:
		App() = default;
		~App() = default;

		/**
		 * Retrieve the GSettings instance to be able to access GTK settings options
		 * @brief Retrieve GSettings instance
		 * @return The GSettings instances
		 * @author David Tkachuk
		 */
		GSettings* getSettings();

		/**
		 * Starts the GTK Application, setups up the important windowing stuff, and then opens
		 * the window. Also initializes the GSettings instance.
		 * @brief Starts the GTK Application
		 * @param argc The number of CLI arguments
		 * @param argv Array of string CLI arguments
		 * @author David Tkachuk
		 */
		void Start(int argc, char **argv);

		/**
		 * Retrieve the status of the application
		 * @brief Retrieve the status of the application
		 * @return The status of the application
		 * @author David Tkachuk
		 */
		int GetStatus();

		/**
		 * Create a new window instance for the HomeHive app, and then renders all its components.
		 * @brief Create the GTK Window
		 * @author David Tkachuk
		 */
		void CreateWindow();

		/**
		 * Application activation handler, which is called whenever the app is runned, and
		 * just creates a new window.
		 * @brief Application activation handler
		 * @param app The GTK Application instance
		 * @param data The HomeHive core App instance
		 * @author David Tkachuk
		 */
		static const void OnActivate(GtkApplication *app, App* data);
};

#endif //HOMEHIVE_APP_H
