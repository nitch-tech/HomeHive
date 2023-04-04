//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_WEATHERCOMPONENT_H
#define HOMEHIVE_WEATHERCOMPONENT_H

#include <gtk/gtk.h>
#include "GuiComponent.h"
#include "../../request/weather.h"

class WeatherComponent: public GuiComponent {
	private:
		GtkImage* imgWeatherIcon;
		GtkWidget* lblWeatherInfo;
		Weather* weather;

	public:
		WeatherComponent();
		~WeatherComponent();

		void setup() override;
		void show() override;

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 *
		 * @todo Ability to change the weather location
		 */
		void settingsUpdated() override;

		/**
		 * Updates the weather information
		 *
		 * Fetches the latest weather information from the Weather API,
		 * and then will attempt to render information (temperature) and an icon.
		 */
		void updateWeather();

	private:
		/**
		 * Retrieves the filename of the icon to use for the weather
		 *
		 * @return A string containing the filename relative path of the icon
		 */
		std::string getIconFilename();

		/**
		 * Loads an icon from a file path, and will load and render it
		 *
		 * @param imagePath The file path of the icon image to load and display
		 */
		void setIcon(const std::string imagePath);

		/**
		 * Sets the text of the weather information label
		 *
		 * @param text The text to set the label to
		 */
		void setInfoText(const gchar* text);
};


#endif //HOMEHIVE_WEATHERCOMPONENT_H
