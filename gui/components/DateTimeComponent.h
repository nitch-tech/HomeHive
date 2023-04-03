//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_DATETIMECOMPONENT_H
#define HOMEHIVE_DATETIMECOMPONENT_H

#include <gtk/gtk.h>
#include "GuiComponent.h"

class DateTimeComponent: public GuiComponent {
	private:
		GtkWidget* container;
		GtkLabel* lblTime;
		GtkLabel* lblDate;

	public:
		DateTimeComponent();
		~DateTimeComponent();


		void setDateAndTime(char* date, char* time);

		void setup() override;
		void show() override;
		void hide() override;
};


#endif //HOMEHIVE_DATETIMECOMPONENT_H
