//
// Created by dave on 13/03/23.
//

#include <iostream>
#include "HomeView.h"
#include "../event/Timer.h"
#include "../request/weather.h"
#include <gtk/gtk.h>
#include <cmath>

#define DEBUG_GRID 1

/**
 * Size Allocator Signal Handler
 *
 * Whenever the window is resized, the grid is resized to match the window.
 *
 * @param widget The widget that fired the signal
 * @param allocation The new allocation of the widget (window dimemsions)
 * @param data Signal data (grid widget)
 */
static void onSizeAllocate(GtkWidget* widget, GdkRectangle* allocation, gpointer data) {
	GtkWidget* grid = (GtkWidget*) data;
	gtk_widget_set_size_request(grid, allocation->width, allocation->height);
}

/**
 * Add a custom CSS class name to some widget
 *
 * @param widget The widget to add the class to
 * @param className The CSS class name to add
 */
static void addClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, className.c_str());
}

/**
 * Remove a custom CSS class name from some widget
 *
 * @param widget The widget to remove the class from
 * @param className The CSS class name to remove
 */
static void removeClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, className.c_str());
}



HomeView::HomeView(GtkWindow *window) : BaseView(window) {
	this->unsplash = new Unsplash();
	this->weather = new Weather();
}

HomeView::~HomeView() {
	delete this->unsplash;
}

/**
 * Setup the view's layout and grid components
 */
void HomeView::setupLayout() {
	// create the base layout, which is the root widget container
	this->layout = (GtkLayout*) gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(this->window), (GtkWidget*) layout);
	gtk_widget_show((GtkWidget*) layout);

	#ifdef DEBUG_GRID
		addClass((GtkWidget*) layout, "debug");
	#endif

	// load & add the default background image, will be behind everything
	this->imgBackground = (GtkImage*) gtk_image_new_from_file("background.jpg");
	gtk_layout_put(layout, (GtkWidget*) imgBackground, 0, 0);

	// create a new grid, to position our UI elements
	auto gridWidget = gtk_grid_new();
	this->grid = (GtkGrid*) gridWidget;
	addClass(gridWidget, "grid");

	// force align the grid
	gtk_container_set_border_width(GTK_CONTAINER(this->layout), 0);
	gtk_widget_set_halign(gridWidget, GTK_ALIGN_FILL);
	gtk_widget_set_valign(gridWidget, GTK_ALIGN_FILL);

	// try to match the grid to the window's size, but do note this isn't enough
	// hence we need to register the size-allocate signal to dynamically make it responsive
	// to whenever the window is resized (or fullscreen)
	int width, height;
	gtk_window_get_size(GTK_WINDOW(window), &width, &height);
	gtk_widget_set_size_request(gridWidget, width, height);

	// force grid to expand to fill the window, but i haven't noticed this doing anything?
	// @TODO investigate this, maybe i'm going mad?
	gtk_widget_set_vexpand(gridWidget, true);
	gtk_widget_set_hexpand((GtkWidget*) this->grid, true);

	// add the grid to the layout
	gtk_layout_put(layout, (GtkWidget*) this->grid, 0, 0);
}

/**
 * Setup important HomeView functionality, such as signals and stylings
 */
void HomeView::registerInteractivity() {
	// register size-allocate signal to dynamically resize grid to window
	g_signal_connect(this->window, "size-allocate", G_CALLBACK(onSizeAllocate), this->grid);

	// create our timer, which does some background work frequently
	Timer* timer = new Timer(this);
	timer->Register();

	// load the CSS file, and set up styles
	auto provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "resources/homeview.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * Setup the HomeView's widgets
 */
void HomeView::drawWidgets() {
	// create a container for the date and time
	this->dateTimeContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(this->grid, this->dateTimeContainer, 0, 0, 1, 1);

	// create the time label
	GtkWidget* lblTime = gtk_label_new_with_mnemonic("00:00");
	this->lblTime = (GtkLabel*) lblTime;
	// gtk_widget_set_size_request(lblTime, 30, 50);
	addClass(lblTime, "lblTime");
	gtk_misc_set_alignment(GTK_MISC(lblTime), 0, 0); // allign left, there's no CSS property for this
	gtk_box_pack_start(GTK_BOX(this->dateTimeContainer), lblTime, FALSE, FALSE, 0);

	// create the date label
	GtkWidget* lblDate = gtk_label_new_with_mnemonic("May 69th 1969");
	this->lblDate = (GtkLabel*) lblDate;
	addClass(lblDate, "lblDate");
	gtk_misc_set_alignment(GTK_MISC(lblDate), 0, 0); // align left
	gtk_box_pack_start(GTK_BOX(this->dateTimeContainer), lblDate, FALSE, FALSE, 0);

	GtkWidget* topSeperator = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, topSeperator, 1, 0, 1, 1);
	gtk_widget_set_vexpand(topSeperator, true);
	gtk_widget_set_hexpand(topSeperator, true);
	addClass(topSeperator, "topSeperator");

	GtkWidget* midSeperator = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, midSeperator, 0, 1, 3, 2);
	gtk_widget_set_vexpand(midSeperator, true);
	gtk_widget_set_hexpand(midSeperator, true);
	addClass(midSeperator, "midSeperator");

	// create the greeting label
	GtkWidget* lblGreeting = gtk_label_new_with_mnemonic("Howdy, unknown user!");
	this->lblGreeting = (GtkLabel*) lblGreeting;
	addClass(lblGreeting, "lblGreeting");
	gtk_misc_set_alignment(GTK_MISC(lblGreeting), 1.0, 0.0);
	gtk_grid_attach(this->grid, lblGreeting, 2, 0, 1, 1);

	// create weather's box container
	GtkWidget* boxWeather = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, boxWeather, 2, 3, 1, 1);
	addClass(boxWeather, "boxWeather");
	gtk_widget_set_vexpand(boxWeather, true);
	gtk_widget_set_hexpand(boxWeather, true);

	gchar *text;
	if (this->weather->fetchWeatherData() != 0) {
		text = g_strdup_printf("Not connected... try again l8r");

	} else {
		text = g_strdup_printf("The current weather in London is %d °C", this->weather->getTempRounded());
	}

	GtkWidget* lblWeather = gtk_label_new_with_mnemonic(text);
	gtk_widget_override_font(lblWeather, pango_font_description_from_string("Tahoma 20"));
//	gtk_widget_set_size_request(lblWeather, 30, 10);
//	gtk_widget_set_vexpand(lblWeather, true);
//	gtk_widget_set_hexpand(lblWeather, true);
	gtk_misc_set_alignment(GTK_MISC(lblWeather), 1, 0);

	gtk_box_pack_end(GTK_BOX(boxWeather), lblWeather, TRUE, TRUE, 0);

	GtkWidget *image = gtk_image_new();
	std::string imagePath;
	int condId = this->weather->getCondId();
	if (condId >= 200 && condId <= 232) {
		imagePath = "../images/cloud.bolt.png";
	} else if (condId >= 300 && condId <= 321) {
		imagePath = "../images/cloud.drizzle.png";
	} else if (condId >= 500 && condId <= 531) {
		imagePath = "../images/cloud.drizzle.png";
	} else if (condId >= 600 && condId <= 622) {
		imagePath = "../images/cloud.snow.png";
	} else if (condId >= 701 && condId <= 781) {
		imagePath = "../images/sun.max.png";
	} else if (condId == 800) {
		imagePath = "../images/cloud.drizzle.png";
	} else if (condId >= 801 && condId <= 804) {
		imagePath = "../images/cloud.png";
	} else {
		imagePath = "../images/cloud.png";
	}

	// resize image  pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(imagePath.c_str(), NULL);
	GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, 96, 96, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), scaled);
	gtk_misc_set_alignment(GTK_MISC(image), 1, 0);
	gtk_box_pack_start(GTK_BOX(boxWeather), image, FALSE, FALSE, 0);
}

void HomeView::setDateAndTime(char *date, char *time) {
	gtk_label_set_text(this->lblDate, date);
	gtk_label_set_text(this->lblTime, time);
}

void HomeView::changeBackgroundImage() {
	// fetch a random background from unsplash API
	auto bg = this->unsplash->getRandomBackground();
	if (bg == nullptr) {
		return;
	}

	// try to download the background
	if (!this->unsplash->downloadBackground(bg, 1920, 1080)) {
		return;
	}

	// reload the background image
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
