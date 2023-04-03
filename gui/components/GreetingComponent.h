//
// Created by dave on 03/04/23.
//

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

		void setup() override;
		void show() override;
		void hide() override;

	private:
		gchar* getGreetingMessage();
};


#endif //HOMEHIVE_GREETINGCOMPONENT_H
