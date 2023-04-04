//
// Created by dave on 13/03/23.
//

#include <iostream>
#include <cmath>
#include <gtk/gtk.h>
#include <glib.h>
#include <algorithm>
#include "HomeView.h"
#include "../event/Timer.h"
#include "GuiHelpers.h"
#include "components/GreetingComponent.h"

//#include <sigc++-2.0/sigc++/sigc++.h>
//#define DEBUG_GRID 1

/**
 * Size Allocator Signal Handler
 *
 * Whenever the window is resized, the grid is resized to match the window.
 *
 * @param widget The widget that fired the signal
 * @param allocation The new allocation of the widget (window dimemsions)
 * @param data Signal data (grid widget)
 */
static void onSizeAllocate(GtkWidget* widget, GdkRectangle* allocation, HomeView* data) {
	data->onWindowResize(allocation);
}


HomeView::HomeView(GtkWindow *window, GSettings* settings) : BaseView(window, settings) {
	this->components = std::vector<GuiComponent*>();
	components.push_back(this->dateTimeComponent = new DateTimeComponent());
	components.push_back(this->weatherComponent = new WeatherComponent());
	components.push_back(this->newsComponent = new NewsComponent());
	components.push_back(this->alarmComponent = new AlarmComponent());
	components.push_back(new GreetingComponent(settings));

	this->unsplash = new Unsplash();
}

HomeView::~HomeView() {
	delete this->weatherComponent;
	delete this->dateTimeComponent;
	delete this->newsComponent;
	delete this->alarmComponent;
	this->components.clear();
	delete this->unsplash;
}
/*
void HomeView::update_labels(){
	//g_print(g_get_application_id());
	GSettings* settings = g_settings_new("ca.uwo.cs3307.homehive");
	const gchar* name = g_settings_get_string(settings,"name");
	gchar* greeting = g_strdup_printf("Howdy, %s!", name);
	gtk_label_set_text(lblGreeting, greeting);

	int interval = g_settings_get_int(settings,"back");
	Localtimer->SetBackInterval(interval);
}*/

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
	this->imgBackground = (GtkImage*) gtk_image_new();
	this->bgBuff = gdk_pixbuf_new_from_file("background.jpg", NULL);
	gtk_image_set_from_pixbuf(this->imgBackground, this->bgBuff);
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
	g_signal_connect(this->window, "size-allocate", G_CALLBACK(onSizeAllocate), this);

	// create our timer, which does some background work frequently
	Timer* timer = Timer::getInstance(this);
	timer->Register();
	timer->SetBackgroundInterval(Settings::getInstance()->getBackgroundInterval());

	// load the CSS file, and set up styles
	auto provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "resources/homeview.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * Setup the HomeView's widgets
 */
void HomeView::drawWidgets() {
	// setup all the components for the GUI
	for (auto component : this->components) {
		component->setParentGrid(this->grid);
		component->setup();
		component->show();
	}

	this->addSeperator("topSeperator", 1, 0, 1, 1);
	this->addSeperator("midSeperator", 0, 1, 3, 2);
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
	// gtk_image_set_from_file(this->imgBackground, this->unsplash->getBackgroundImage().c_str());

	this->LoadBackgroundImage(this->unsplash->getBackgroundImage());
}

void HomeView::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		gtk_window_fullscreen(this->window);
	} else {
		gtk_window_unfullscreen(this->window);
	}
}

/**
 * Loads a new background image from a given file path
 *
 * @param fname The file path to load an image from
 */
void HomeView::LoadBackgroundImage(std::string fname) {
	this->bgBuff = gdk_pixbuf_new_from_file(fname.c_str(), NULL);
	this->DrawBackgroundScaled();

	// refresh and reload background
	gtk_widget_queue_draw((GtkWidget*) this->imgBackground);
	gtk_widget_show((GtkWidget*) this->imgBackground);
}

/**
 * Draws the background image, scaled to the window size
 *
 * @param width The window width
 * @param height The window height
 * @todo Look into gdk_pixbuf_scale(), to be able to use the offset, so the background
 * can be centered to the window.
 */
void HomeView::DrawBackgroundScaled(int width, int height) {
	// if invalid, or no size was specific, then we'll have to manually get window size.
	if (width < 1 || height < 1) {
		gtk_window_get_size(this->window, &width, &height);
	}

	// retrieve the background image size
	int bgWidth = gdk_pixbuf_get_width(this->bgBuff);
	int bgHeight = gdk_pixbuf_get_height(this->bgBuff);

	// calculate the image ratio, respective to the window size. and we use the LARGEST ratio, so we can
	// cover the entire window screen, but still maintain aspect raatio
	// float r = std::min((float)width / (float)bgWidth, (float)height / (float)bgHeight);
	float r = std::max((float)width / (float)bgWidth, (float)height / (float)bgHeight);

	std::cout << "Background{W=" << bgWidth << ", H=" << bgHeight << "} Window{W=" <<
		width << ", H="<<height << "} RATIO="<<r << std::endl;

	// scale the buffer image into a new buffer, the final background image to render
	this->bgBuffScaled = gdk_pixbuf_scale_simple(
		this->bgBuff,
		(float) bgWidth * r,
		(float) bgHeight * r,
		GDK_INTERP_NEAREST
	);

	// set the background image
	gtk_image_set_from_pixbuf(this->imgBackground, this->bgBuffScaled);
}

/**
 * On Window Resize
 *
 * Whenever the window is resized, full screen, maximized, etc, this function will be called.
 * The actual implementation is to resize the background image to fit the window size, and to
 * resize the grid to fit the window size, to make it perfectly responsive.
 *
 * @param size The new window size structure
 */
void HomeView::onWindowResize(GdkRectangle *size) {
	BaseView::onWindowResize(size);
	std::cout << "resized to w=" << size->width << ", h=" << size->height << ", x=" << size->x << ", y=" << size->y << std::endl;

	// resize the grid to fit the window
	gtk_widget_set_size_request(GTK_WIDGET(this->grid), size->width, size->height);

	// int width, height;
	// gtk_window_get_size(data->getWindow(), &width, &height);

	// redraw the background to scale to the window size
	this->DrawBackgroundScaled(size->width, size->height);
}


/**
 * Retrieves the DateTimeComponent instance, which contains and manages
 * the date and time widgets on screen.
 *
 * @return The current DateTimeComponent instance
 */
DateTimeComponent *HomeView::getDateTimeComponent() {
	return this->dateTimeComponent;
}


/**
 * Add an empty box widget to the grid, which is used to seperate
 * all the UI widgets within the entire grid to align them.
 *
 * @param id The ID of the widget
 * @param left The left position of the widget in the grid
 * @param top The top position of the widget in the grid
 * @param width The width of the widget in the grid
 * @param height The height of the widget in the grid
 */
void HomeView::addSeperator(const std::string id, int left, int top, int width, int height) {
	GtkWidget* sep = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//	gtk_widget_set_name(sep, id.c_str());
	gtk_widget_set_vexpand(sep, true);
	gtk_widget_set_hexpand(sep, true);
	addClass(sep, id);
	gtk_grid_attach(this->grid, sep, left, top, width, height);
}

/**
 * Retrieves the WeatherComponent instance, which handles retrieving and rendering
 * information about the current weather.
 *
 * @return The current WeatherComponent instance
 */
WeatherComponent* HomeView::getWeatherComponent() {
	return this->weatherComponent;
}

/**
 * Retrieves the NewsComponent instance, which handles retrieving and rendering
 * information about the current news.
 *
 * @return The current NewsComponent instance
 */
NewsComponent* HomeView::getNewsComponent() {
	return this->newsComponent;
}

/**
 * Update the view, something (ie: a setting) was changed, so
 * triggger various components to update themselves.
 */
void HomeView::update() {
	g_print("Updating HomeView after settings change\n");

	BaseView::update();
	for (auto &component : this->components) {
		component->settingsUpdated();
	}
	Timer::getInstance(this)
		->SetBackgroundInterval(Settings::getInstance()->getBackgroundInterval());
}

/**
 * Retrieves the AlarmComponent instance, which handles retrieving and rendering
 * information about the current alarms.
 *
 * @return The current AlarmComponent instance
 */
AlarmComponent *HomeView::getAlarmComponent() {
	return this->alarmComponent;
}
