//
// Created by dave on 03/04/23.
//

#include "WeatherComponent.h"
#include "../GuiHelpers.h"

WeatherComponent::WeatherComponent() {
	this->weather = new Weather();
}

WeatherComponent::~WeatherComponent() {
	delete this->weather;
}

void WeatherComponent::setup() {
	// create weather's box container
	GtkWidget* boxWeather = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	this->container = (GtkBox*) boxWeather;
	addClass(boxWeather, "boxWeather");

	// create the weather label
	this->lblWeatherInfo = gtk_label_new_with_mnemonic("Finding the sun...");
	gtk_misc_set_alignment(GTK_MISC(this->lblWeatherInfo), 0.5, 0.5);
	addClass(this->lblWeatherInfo, "lblWeather");
	gtk_box_pack_end(this->container, this->lblWeatherInfo, TRUE, TRUE, 0);

	// create weather icon
	this->imgWeatherIcon = (GtkImage*) gtk_image_new();
	gtk_misc_set_alignment(GTK_MISC(imgWeatherIcon), 0.5, 0.5);
	gtk_box_pack_start(this->container, GTK_WIDGET(imgWeatherIcon), FALSE, FALSE, 0);

}

void WeatherComponent::show() {
	gtk_grid_attach(this->parentGrid, (GtkWidget*) this->container, 2, 3, 1, 1);
}

void WeatherComponent::hide() {
}

/**
 * Updates the weather information
 *
 * Fetches the latest weather information from the Weather API,
 * and then will attempt to render information (temperature) and an icon.
 */
void WeatherComponent::updateWeather() {
	if (this->weather->fetchWeatherData() != 0) {
		this->setInfoText("Weather data unavailable");
		return;
	}

	gchar* text = g_strdup_printf(
		"%s\nCurrently: %d°C | Feels Like: %i°C",
		this->weather->getLocationName().c_str(),
		this->weather->getTempRounded(),
		this->weather->getTempFeelsLikeRounded()
	);
	this->setInfoText(text);

	this->setIcon(this->getIconFilename());
}

/**
 * Retrieves the filename of the icon to use for the weather
 *
 * @return A string containing the filename relative path of the icon
 */
std::string WeatherComponent::getIconFilename() {
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

	return imagePath;
}

/**
 * Loads an icon from a file path, and will load and render it
 *
 * @param imagePath The file path of the icon image to load and display
 */
void WeatherComponent::setIcon(const std::string imagePath) {
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(imagePath.c_str(), NULL);
	GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, 96, 96, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(this->imgWeatherIcon, scaled);
}

/**
 * Sets the text of the weather information label
 *
 * @param text The text to set the label to
 */
void WeatherComponent::setInfoText(const gchar* text) {
	gtk_label_set_text((GtkLabel*) this->lblWeatherInfo, text);
}
