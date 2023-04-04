//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_DATETIMECOMPONENT_H
#define HOMEHIVE_DATETIMECOMPONENT_H

#include <gtk/gtk.h>
#include "GuiComponent.h"

class DateTimeComponent: public GuiComponent {
	private:
		GtkLabel* lblTime;
		GtkLabel* lblDate;

	public:
		DateTimeComponent();
		~DateTimeComponent();


		void setDateAndTime(char* date, char* time);

		void setup() override;
		void show() override;

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 *
		 * @todo Ability to change the datetime format
		 */
		void settingsUpdated() override;
};


#endif //HOMEHIVE_DATETIMECOMPONENT_H
