//
// Created by dave on 03/04/23.
//

#include "GuiComponent.h"


GuiComponent::GuiComponent() {
}

GuiComponent::~GuiComponent() {
}

void GuiComponent::setParentGrid(GtkGrid* parentGrid) {
	this->parentGrid = parentGrid;
}

GtkBox *GuiComponent::getContainer() {
	return this->container;
}
