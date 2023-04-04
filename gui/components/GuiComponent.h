//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_GUICOMPONENT_H
#define HOMEHIVE_GUICOMPONENT_H

#include <gtk/gtk.h>

/**
 * GUI Component
 * Represents a single component of the GUI
 *
 * @brief GUI Component
 * @author David Tkachuk
 */
class GuiComponent {
	protected:
		GtkBox* container;
		GtkGrid* parentGrid;

	public:
		GuiComponent();
		~GuiComponent();

		/**
		 * Set the parent grid, who this component will be added to
		 *
		 * @brief Set the parent grid
		 * @param parentGrid The parent grid
		 * @author David Tkachuk
		 */
		void setParentGrid(GtkGrid* parentGrid);

		/**
		 * Get the container of this component
		 * @brief Get the container widget
		 * @return The container widget (box)
		 * @author David Tkachuk
		 */
		GtkBox* getContainer();

		/**
		 * Show the GUI component
		 * @brief Show the GUI component
		 * @author David Tkachuk
		 */
		virtual void setup() = 0;

		/**
		 * Hide the GUI component
		 * @brief Hide the GUI component
		 * @todo implement this pls
		 * @author David Tkachuk
		 */
		virtual void show() = 0;

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 * @brief Trigger component to update its info
		 * @author David Tkachuk
		 */
		virtual void settingsUpdated() = 0;
};


#endif //HOMEHIVE_GUICOMPONENT_H
