#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
//#include "App.h"


#ifndef HOMEHIVE_VIEWBASE_H
#define HOMEHIVE_VIEWBASE_H

class BaseView {
	protected:
		// App* app;
		GSettings* settings;
		GtkWindow* window;
		bool visible;

	public:
		BaseView(GtkWindow* window, GSettings* settings);
		// BaseView(App* app, GtkWindow* window);
		~BaseView();

		// App* getApp();
		bool isVisible();

		GtkWindow* getWindow();

		virtual void setup();
		virtual void show();
		virtual void hide();

		/**
		 * Update the view, something (ie: a setting) was changed, so
		 * triggger various components to update themselves.
		 */
		virtual void update();

		/**
		 * On Window Resize
		 *
		 * Whenever the window is resized, full screen, maximized, etc, this function will be called.
		 * The actual implementation is to resize the background image to fit the window size, and to
		 * resize the grid to fit the window size, to make it perfectly responsive.
		 *
		 * @param size The new window size structure
		 */
		virtual void onWindowResize(GdkRectangle* size);

	protected:
		virtual void drawWidgets() = 0;
		virtual void registerInteractivity() = 0;
		virtual void setupLayout() = 0;
};


#endif //HOMEHIVE_VIEWBASE_H
