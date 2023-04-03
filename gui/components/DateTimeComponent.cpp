//
// Created by dave on 03/04/23.
//

#include <iostream>
#include "DateTimeComponent.h"
#include "../GuiHelpers.h"

DateTimeComponent::DateTimeComponent() {

}

DateTimeComponent::~DateTimeComponent() {

}

void DateTimeComponent::setDateAndTime(char *date, char *time) {
	std::cout << "setDateAndTime, date="<<date<<", time="<<time<<std::endl;
	gtk_label_set_text(this->lblTime, time);
	gtk_label_set_text(this->lblDate, date);
}

void DateTimeComponent::setup() {
	this->container = (GtkBox*) gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// create the time label
	GtkWidget* time = gtk_label_new_with_mnemonic("00:00");
	this->lblTime = (GtkLabel*) time;
	// gtk_widget_set_size_request(lblTime, 30, 50);
	addClass(time, "lblTime");
	gtk_misc_set_alignment(GTK_MISC(lblTime), 0, 0); // allign left, there's no CSS property for this
	gtk_box_pack_start(GTK_BOX(this->container), time, FALSE, FALSE, 0);

	// create the date label
	GtkWidget* date = gtk_label_new_with_mnemonic("May 69th 1969");
	this->lblDate = (GtkLabel*) date;
	addClass(date, "lblDate");
	gtk_misc_set_alignment(GTK_MISC(date), 0, 0); // align left
	gtk_box_pack_start(GTK_BOX(this->container), date, FALSE, FALSE, 0);
}

void DateTimeComponent::show() {
	gtk_grid_attach(this->parentGrid, (GtkWidget*) this->container, 0, 0, 1, 1);
}

void DateTimeComponent::hide() {

}
