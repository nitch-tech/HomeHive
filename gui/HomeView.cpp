//
// Created by dave on 13/03/23.
//

#include <iostream>
#include "HomeView.h"
#include "../event/Timer.h"
#include "weather.h"
#include <gtk/gtk.h>

void HomeView::setup() {
//	this->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//	gtk_container_add(GTK_CONTAINER(this->window), this->vbox);

	this->grid = (GtkTable*) gtk_table_new(3, 3, TRUE);
	gtk_container_add(GTK_CONTAINER(this->window), (GtkWidget*) this->grid);


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

    //Just trying something delete later
    Weather* weatherData = new Weather();
    gchar *text;
    if (weatherData->fetchWeatherData() != 0) {
        text = g_strdup_printf("Not connected... try again l8r");

    } else {
        double temp = weatherData->getTemp();
        int rounded = std::round(temp);
        std::cout << weatherData << "This is a test";
        text = g_strdup_printf("The current weather in London is %d °C", rounded);
    }

    GtkWidget* lblWeather = gtk_label_new_with_mnemonic(text);
    gtk_widget_override_font(lblWeather, pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(lblWeather, 30, 10);
    gtk_widget_set_vexpand(lblWeather, true);
    gtk_widget_set_hexpand(lblWeather, true);
    gtk_table_attach_defaults(this->grid, lblWeather, 0, 1, 0, 1);


    GtkWidget *image;
    std::string imagePath;
    int condId = weatherData ->getCondId();
    if (condId >= 200 && condId <= 232 ) {
        image = gtk_image_new_from_file("../images/cloud.bolt.png");
    } else if (condId >= 300 && condId <= 321 ) {
        image = gtk_image_new_from_file("../images/cloud.drizzle.png");
    }else if (condId >= 500 && condId <= 531 ) {
        image = gtk_image_new_from_file("../images/cloud.drizzle.png");
    }else if (condId >= 600 && condId <= 622 ) {
        image = gtk_image_new_from_file("../images/cloud.snow.png");
    }else if (condId >= 701 && condId <= 781 ) {
        image = gtk_image_new_from_file("../images/sun.max.png");
    } else if (condId == 800 ) {
        image = gtk_image_new_from_file("../images/cloud.drizzle.png");
    }else if (condId >= 801 && condId <= 804 ) {
        image = gtk_image_new_from_file("../images/cloud.png");
    } else {
        image = gtk_image_new_from_file("../images/cloud.png");
    }


    gtk_widget_set_size_request(image, 5, 5);
    gtk_widget_set_vexpand(image, true);
    gtk_widget_set_hexpand(image, true);
    gtk_table_attach_defaults(this->grid, image, 0, 1, 0, 2);

}

void HomeView::show() {
}

void HomeView::hide() {
}

HomeView::HomeView(GtkWindow *window) : BaseView(window) {
}

HomeView::~HomeView() {
}

void HomeView::setDateAndTime(char *date, char *time) {
	gtk_label_set_text(this->lblDate, date);
	gtk_label_set_text(this->lblTime, time);
	//std::cout << "aaa" << date << "=="<<time << std::endl;
}
