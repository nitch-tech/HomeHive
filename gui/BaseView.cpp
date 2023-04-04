//
// Created by dave on 12/03/23.
//

#include "BaseView.h"

/**
 * BaseView constructor
 * @brief BaseView constructor
 * @param window GTK window instance (what to render in)
 * @param settings GTK Settings instance (access/modify settings)
 * @author David Tkachuk
 */
BaseView::BaseView(GtkWindow* window, GSettings* settings) {
	this->window = window;
	this->settings = settings;
	this->visible = false;
}

BaseView::~BaseView() {
}
/*
App *BaseView::getApp() {
	return this->app;
}*/

bool BaseView::isVisible() {
	return this->visible;
}

void BaseView::setup() {
	this->setupLayout();
	this->drawWidgets();
	this->registerInteractivity();
}

void BaseView::show() {
	this->visible = true;
}

GtkWindow *BaseView::getWindow() {
	return this->window;
}

void BaseView::onWindowResize(GdkRectangle* size) {
}

void BaseView::update() {
}
