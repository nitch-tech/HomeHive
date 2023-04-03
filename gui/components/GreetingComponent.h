#ifndef HOMEHIVE_GREETINGCOMPONENT_H
#define HOMEHIVE_GREETINGCOMPONENT_H

#include <gtk/gtk.h>
#include "GuiComponent.h"

class GreetingComponent: public GuiComponent {
	private:
		GSettings* settings;
		GtkLabel* lblGreeting;
		GtkWidget* btnSettings;

	public:
		GreetingComponent(GSettings* settings);
		~GreetingComponent();

		static void onSettingsClicked(GtkWidget *widget, gpointer data);

		void setup() override;
		void show() override;

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 */
		void settingsUpdated() override;

	private:
		gchar* getGreetingMessage();
};


#endif //HOMEHIVE_GREETINGCOMPONENT_H
