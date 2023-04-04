//
// Created by dave on 03/04/23.
//

/**
 * @brief Create a GuiComponent
 */

#include "GuiComponent.h"

/**
 * @brief GuiComponent constructor
 */
GuiComponent::GuiComponent() {
}
/**
 * @brief GuiComponent deconstructor
 */
GuiComponent::~GuiComponent() {
}
/**
 * set the grid
 * @param parentGrid
 */
void GuiComponent::setParentGrid(GtkGrid* parentGrid) {
	this->parentGrid = parentGrid;
}
/**
 * Get the container
 * @return GtkBox object
 */
GtkBox *GuiComponent::getContainer() {
	return this->container;
}
