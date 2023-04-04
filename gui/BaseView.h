#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
//#include "App.h"


#ifndef HOMEHIVE_VIEWBASE_H
#define HOMEHIVE_VIEWBASE_H

/**
 * BaseView class defines the basic structure of a view for the HomeHive application.
 * @brief BaseView class basic structure of a view
 * @author David Tkachuk
 */
class BaseView {
	protected:
		// App* app;
		GSettings* settings;
		GtkWindow* window;
		bool visible;

	public:
		/**
		 * BaseView constructor
		 * @brief BaseView constructor
		 * @param window GTK window instance (what to render in)
		 * @param settings GTK Settings instance (access/modify settings)
		 * @author David Tkachuk
		 */
		BaseView(GtkWindow* window, GSettings* settings);
		// BaseView(App* app, GtkWindow* window);
		~BaseView();

		// App* getApp();

		/**
		 * Check if the view is visible
		 * @brief Check if the view is visible
		 * @return True if visible, false otherwise
		 * @author David Tkachuk
		 */
		bool isVisible();

		/**
		 * Retrieve the GTK Window instance
		 * @brief Retrieve the GTK Window instance
		 * @return The GTK Window instance
		 * @author David Tkachuk
		 */
		GtkWindow* getWindow();

		/**
		 * Setup the view, this is called when the view is first created, and is used to
		 * setup the layout, draw the widgets, and register the interactivity.
		 * @brief Setup the view, prepare its widgets and stuffff
		 * @author David Tkachuk
		 */
		virtual void setup();

		/**
		 * Show the view, this is called when the view is first created and render it all.
		 * @brief Show the view
		 * @author David Tkachuk
		 */
		virtual void show();

		/**
		 * Update the view, something (ie: a setting) was changed, so triggger various components to update themselves.
		 * @brief Update the view after settings changed
		 * @author David Tkachuk
		 */
		virtual void update();

		/**
		 * On Window Resize
		 *
		 * Whenever the window is resized, full screen, maximized, etc, this function will be called.
		 * The actual implementation is to resize the background image to fit the window size, and to
		 * resize the grid to fit the window size, to make it perfectly responsive.
		 *
		 * @brief Force window to adjust after window resize
		 * @param size The new window size structure
		 * @author David Tkachuk
		 */
		virtual void onWindowResize(GdkRectangle* size);

	protected:
		/**
		 * Draw all widgets in the view, rendering them to the window.
		 * @brief Draw all widgets in the view
		 * @author David Tkachuk
		 */
		virtual void drawWidgets() = 0;

		/**
		 * Register interactivity and signals/events for all widgets in the view
		 * @brief Register interactivity & events
		 * @author David Tkachuk
		 */
		virtual void registerInteractivity() = 0;

		/**
		 * Setup the layout of the view, this is called when the view is first created, and is used to
		 * setup the basic structure/grid and how widgets should be placed.
		 * @brief Setup the layout of the view
		 * @author David Tkachuk
		 */
		virtual void setupLayout() = 0;
};


#endif //HOMEHIVE_VIEWBASE_H
