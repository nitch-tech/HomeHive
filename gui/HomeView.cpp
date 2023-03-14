//
// Created by dave on 13/03/23.
//

#include <iostream>
#include "HomeView.h"
#include "../event/Timer.h"

static void addClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, className.c_str());
}

void HomeView::setup() {
//	this->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//	gtk_container_add(GTK_CONTAINER(this->window), this->vbox);

	this->layout = (GtkLayout*) gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(this->window), (GtkWidget*) layout);
	gtk_widget_show((GtkWidget*) layout);

	this->imgBackground = (GtkImage*) gtk_image_new_from_file("background.jpg");
	gtk_layout_put(layout, (GtkWidget*) imgBackground, 0, 0);

	this->grid = (GtkGrid*) gtk_grid_new();
	gtk_layout_put(layout, (GtkWidget*) this->grid, 0, 0);
	addClass((GtkWidget*)this->grid, "grid");


	gtk_widget_set_vexpand((GtkWidget*) this->grid, true);
	gtk_widget_set_hexpand((GtkWidget*) this->grid, true);

	this->messageContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//	gtk_container_add(GTK_CONTAINER(this->vbox), this->messageContainer);



	gtk_grid_attach(this->grid, this->messageContainer, 0, 0, 1, 1);
//	gtk_table_attach_defaults(this->grid, this->messageContainer, 0, 1, 0, 1);

	GtkWidget* lblTime = gtk_label_new_with_mnemonic("00:00");
	this->lblTime = (GtkLabel*) lblTime;
	gtk_widget_set_size_request(lblTime, 30, 50);
	gtk_box_pack_start(GTK_BOX(this->messageContainer), lblTime, FALSE, FALSE, 0);
	addClass(lblTime, "lblTime");

	GtkWidget* lblDate = gtk_label_new_with_mnemonic("May 69th 1969");
	this->lblDate = (GtkLabel*) lblDate;
	gtk_widget_set_size_request(lblDate, 30, 50);
	gtk_box_pack_start(GTK_BOX(this->messageContainer), lblDate, FALSE, FALSE, 0);
	addClass(lblDate, "lblDate");

	GtkWidget* lblGreeting = gtk_label_new_with_mnemonic("HOWDY DAVE!");
	this->lblGreeting = (GtkLabel*) lblGreeting;
//	auto align = gtk_alignment_new(1.0, 0.0, 0.0, 0.0);
	gtk_widget_set_size_request(lblGreeting, 30, 10);
	addClass(lblGreeting, "lblGreeting");
	gtk_widget_set_vexpand(lblGreeting, true);
	gtk_widget_set_hexpand(lblGreeting, true);

//	gtk_table_attach_defaults(this->grid, lblGreeting, 1, 2, 0, 1);

	gtk_grid_attach(this->grid, lblGreeting, 1, 0, 1, 1);

//	auto cb = [this](char* a, char* b) {
//		this->setDateAndTime(a, b);
//	};
	Timer* timer = new Timer(this);
	timer->Register();


	auto provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "resources/homeview.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

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
