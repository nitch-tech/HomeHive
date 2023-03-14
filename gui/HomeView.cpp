//
// Created by dave on 13/03/23.
//

#include <iostream>
#include "HomeView.h"
#include "../event/Timer.h"

void HomeView::setup() {
//	this->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//	gtk_container_add(GTK_CONTAINER(this->window), this->vbox);

	this->layout = (GtkLayout*) gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(this->window), (GtkWidget*) layout);
	gtk_widget_show((GtkWidget*) layout);

	this->imgBackground = (GtkImage*) gtk_image_new_from_file("background.jpg");
	gtk_layout_put(layout, (GtkWidget*) imgBackground, 0, 0);

	this->grid = (GtkTable*) gtk_table_new(3, 3, TRUE);
//	gtk_container_add(GTK_CONTAINER(this->window), (GtkWidget*) this->grid);
	gtk_layout_put(layout, (GtkWidget*) this->grid, 0, 0);


	gtk_widget_set_vexpand((GtkWidget*) this->grid, true);
	gtk_widget_set_hexpand((GtkWidget*) this->grid, true);

	this->messageContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//	gtk_container_add(GTK_CONTAINER(this->vbox), this->messageContainer);


	gtk_table_attach_defaults(this->grid, this->messageContainer, 0, 1, 0, 1);

	GtkWidget* lblTime = gtk_label_new_with_mnemonic("00:00");
	this->lblTime = (GtkLabel*) lblTime;
	gtk_widget_override_font(lblTime, pango_font_description_from_string("Tahoma 36"));
	gtk_widget_set_size_request(lblTime, 30, 50);
	gtk_box_pack_start(GTK_BOX(this->messageContainer), lblTime, FALSE, FALSE, 0);

	GtkWidget* lblDate = gtk_label_new_with_mnemonic("May 69th 1969");
	this->lblDate = (GtkLabel*) lblDate;
	gtk_widget_override_font(lblDate, pango_font_description_from_string("Tahoma 20"));
	gtk_widget_set_size_request(lblDate, 30, 50);
	gtk_box_pack_start(GTK_BOX(this->messageContainer), lblDate, FALSE, FALSE, 0);

	GtkWidget* lblGreeting = gtk_label_new_with_mnemonic("HOWDY DAVE!");
	this->lblGreeting = (GtkLabel*) lblGreeting;
//	auto align = gtk_alignment_new(1.0, 0.0, 0.0, 0.0);
	gtk_widget_override_font(lblGreeting, pango_font_description_from_string("Tahoma 20"));
	gtk_widget_set_size_request(lblGreeting, 30, 10);
	gtk_widget_set_vexpand(lblGreeting, true);
	gtk_widget_set_hexpand(lblGreeting, true);

	gtk_table_attach_defaults(this->grid, lblGreeting, 1, 2, 0, 1);

//	auto cb = [this](char* a, char* b) {
//		this->setDateAndTime(a, b);
//	};
	Timer* timer = new Timer(this);
	timer->Register();
}

void HomeView::show() {
}

void HomeView::hide() {
}

HomeView::HomeView(GtkWindow *window) : BaseView(window) {
	this->unsplash = new Unsplash();
}

HomeView::~HomeView() {
	delete this->unsplash;
}

void HomeView::setDateAndTime(char *date, char *time) {
	gtk_label_set_text(this->lblDate, date);
	gtk_label_set_text(this->lblTime, time);
	std::cout << "aaa" << date << "=="<<time << std::endl;
}

void HomeView::changeBackgroundImage() {
	auto bg = this->unsplash->getRandomBackground();
	if (bg == nullptr) {
		return;
	}

	if (!this->unsplash->downloadBackground(bg, 1920, 1080)) {
		return;
	}
	gtk_image_set_from_file(this->imgBackground, this->unsplash->getBackgroundImage().c_str());

	// refresh and reload background
	gtk_widget_queue_draw((GtkWidget*) this->imgBackground);
	gtk_widget_show((GtkWidget*) this->imgBackground);
}

void HomeView::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		gtk_window_fullscreen(this->window);
	} else {
		gtk_window_unfullscreen(this->window);
	}
}
