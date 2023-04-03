//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_GUICOMPONENT_H
#define HOMEHIVE_GUICOMPONENT_H

#include <gtk/gtk.h>

class GuiComponent {
	protected:
		GtkBox* container;
		GtkGrid* parentGrid;

	public:
		GuiComponent();
		~GuiComponent();

		void setParentGrid(GtkGrid* parentGrid);
		GtkBox* getContainer();

		virtual void setup() = 0;
		virtual void show() = 0;

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 */
		virtual void settingsUpdated() = 0;
};


#endif //HOMEHIVE_GUICOMPONENT_H
