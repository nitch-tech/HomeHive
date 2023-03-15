#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
//#include "App.h"


#ifndef HOMEHIVE_VIEWBASE_H
#define HOMEHIVE_VIEWBASE_H

class BaseView {
	protected:
		// App* app;
		GtkWindow* window;
		bool visible;

	public:
		BaseView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~BaseView();

		// App* getApp();
		bool isVisible();

		virtual void setup();
		virtual void show();
		virtual void hide();

	protected:
		virtual void drawWidgets() = 0;
		virtual void registerInteractivity() = 0;
		virtual void setupLayout() = 0;
};


#endif //HOMEHIVE_VIEWBASE_H
