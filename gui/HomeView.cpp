//
// Created by dave on 13/03/23.
//

#include <iostream>
#include <cmath>
#include <gtk/gtk.h>
#include <algorithm>
#include "HomeView.h"
#include "../event/Timer.h"

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
	this->news = new News();
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
	std::cout << "what\n";
//	this->imgBackground = (GtkImage*) gtk_image_new_from_file("background.jpg");
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

	// create the weather label
	this->lblWeather = gtk_label_new_with_mnemonic("Finding the sun...");
	gtk_misc_set_alignment(GTK_MISC(lblWeather), 0.5, 0.5);
	addClass(lblWeather, "lblWeather");
	gtk_box_pack_end(GTK_BOX(boxWeather), lblWeather, TRUE, TRUE, 0);

	// create weather icon
	this->imgWeather = (GtkImage*) gtk_image_new();
	gtk_misc_set_alignment(GTK_MISC(imgWeather), 0.5, 0.5);
	gtk_box_pack_start(GTK_BOX(boxWeather), (GtkWidget*)imgWeather, FALSE, FALSE, 0);

	// create news's box container
	GtkWidget* boxNews = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, boxNews, 0, 3, 1, 1);
	addClass(boxNews, "boxNews");

	// create the news label
	this->lblNews = gtk_label_new_with_mnemonic("What's going on in the world?");
	gtk_misc_set_alignment(GTK_MISC(lblNews), 0.5, 0.5);
	addClass(lblNews, "lblNews");
	gtk_box_pack_end(GTK_BOX(boxNews), lblNews, TRUE, TRUE, 0);

}

void HomeView::updateWeather() {
	gchar *text;
	if (this->weather->fetchWeatherData() != 0) {
		text = g_strdup_printf("Failed to fetch weather");
		gtk_label_set_text((GtkLabel*) this->lblWeather, text);
		return;
	} else {
		text = g_strdup_printf(
						"%s\nCurrently: %d°C | Feels Like: %i°C",
						this->weather->getLocationName().c_str(),
						this->weather->getTempRounded(),
						this->weather->getTempFeelsLikeRounded()
		);
		gtk_label_set_text((GtkLabel*) this->lblWeather, text);
	}

	std::string imagePath;
	int condId = this->weather->getCondId();
	if (condId >= 200 && condId <= 232) {
		imagePath = "resources/icons/cloud.bolt.png";
	} else if (condId >= 300 && condId <= 321) {
		imagePath = "resources/icons/cloud.drizzle.png";
	} else if (condId >= 500 && condId <= 531) {
		imagePath = "resources/icons/cloud.drizzle.png";
	} else if (condId >= 600 && condId <= 622) {
		imagePath = "resources/icons/cloud.snow.png";
	} else if (condId >= 701 && condId <= 781) {
		imagePath = "resources/icons/sun.max.png";
	} else if (condId == 800) {
		imagePath = "resources/icons/cloud.drizzle.png";
	} else if (condId >= 801 && condId <= 804) {
		imagePath = "resources/icons/cloud.png";
	} else {
		imagePath = "resources/icons/cloud.png";
	}

	// resize image  pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(imagePath.c_str(), NULL);
	GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, 96, 96, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgWeather), scaled);
}

void HomeView::updateNews(bool fetchNews){
	gchar *text;
	if(fetchNews == true){
		if (this->news->fetchNewsData() != 0) {
			text = g_strdup_printf("Failed to fetch news");
			gtk_label_set_text((GtkLabel*) this->lblNews, text);
			return;
		}
	}
	
	text = g_strdup_printf(
					"Your Top Stories Today\n%s",
					this->news->getHeadline().c_str()
		);
	gtk_label_set_text((GtkLabel*) this->lblNews, text);

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
