//
// Created by mariam on 2023-03-14.
//
/**
 * @breif header class for weather
 * Information about the current weather is stored in a Weather object
 * @author Mariam Alabi
 */


#ifndef HOMEHIVE_WEATHER_H
#define HOMEHIVE_WEATHER_H


#include <iostream>
#include <fstream>
#include <string>
#include "request.h"

class Weather {
	private:
		std::string locationName;
		double temperatureString;
		float tempFeelsLike;
		int conditionId;

	public:
        /**
         * @brief constructor for a weather object
         */
		Weather();
        /**
         * @brief deconstructor for a weather object
         */
		~Weather();
        /**
         * @brief get the current weather
         * Call a request to openweathermap API to get the current weather data
         */
		int fetchWeatherData();
        /**
         * @brief gets the temperature (as a double)
         * @return the current temperature as a double
         */
		double getTemp();
        /**
        * @brief get the temperature as an integer
        * @return integer that is the current temperature
        */
		int getTempRounded();
        /**
         * @brief get the location of weather
         * get the location of the weather. In our app, it should always be London, Ontario
         * @return location of weather as a string
         */
		std::string getLocationName();

		float getTempFeelsLike();
        /**
         * @brief get what temperature feels like
         *
         * @return what the temperature feels like as an integer
         */
		int getTempFeelsLikeRounded();
        /**
         * @brief get condition id for the weather
         * The condition id describes the current weather (see https://openweathermap.org/weather-conditions for weather codes)
         * The lets the app display an accurate icon that describes the current weather
         * @return an integer that describes the current weather as an id as described by openweathermap
         */
		int getCondId();
};


#endif //HOMEHIVE_WEATHER_H
