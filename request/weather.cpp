//
// Created by mariam on 2023-03-14.
//
/**
 * @brief the class for getting the current weather
 * Weather data is obtained from making a call to OpenWeatherMap API
 * @author Mariam Alabi
 */
#include <string>
#include <nlohmann/json.hpp>
#include "weather.h"

using json = nlohmann::json;

const std::string WEATHER_API_ID = "6058560"; ///OpenWeatherMap gets data using an ID and KEY
const std::string WEATHER_API_KEY = "7caf3dcfe4918513df6c3ddf1b564435"; ///OpenWeatherMap gets data using an ID and KEY

/**
 * @brief constructor initilizing variables
 * The constructor initilizes temperature, condition id, location name, and what the temperature feels like
 */
Weather::Weather() {
	temperatureString = 0;
	conditionId = 0;
	this->locationName = "Unknown";
	this->tempFeelsLike = 0;
}
/**
 * @brief weather deconstructor
 */
Weather::~Weather() = default;

/**
 * @brief get weather data
 * Makes a call to OpenWeatherMap, which has the current weather in a json format
 * The method parses the json object to get relevant data
 * @return 0 if reqest succeeded, -1 if fail
 */
int Weather::fetchWeatherData() {
	Request initial("https://api.openweathermap.org/data/2.5/weather?id=" +
		WEATHER_API_ID + "&appid=" + WEATHER_API_KEY + "&units=metric");

	if (initial.execute()) {
		std::string res = initial.getResponse();
		json data = json::parse(res);

		for (json &weather: data["weather"]) {
			conditionId = weather["id"];
		}

		temperatureString = data["main"]["temp"];
		this->tempFeelsLike = data["main"]["feels_like"];
		this->locationName = data["name"];

		return 0;

	} else {
		std::cerr << "API request returned NULL" << std::endl;
		return -1;
	}

}
/**
 * @brief get the current temperature
 * get the current temperature in the form of a string
 * @return temperature
 */
double Weather::getTemp() {
	return temperatureString;
}

/**
 * @brief Get the conditionID of the current weather
 * OpenweatherMap uses conditionID to describe the current weather. This allows to display an icon that accurately describes the current weather
 * @return condition id
 */
int Weather::getCondId() {
	return conditionId;
}
/**
* @brief get the temperature as an integer
* @return integer that is the current temperature
*/
int Weather::getTempRounded() {
	return (int) std::round(this->temperatureString);
}
/**
 * @brief gets the temperature (as a double)
 * @return the current temperature as a double
 */
float Weather::getTempFeelsLike() {
	return this->tempFeelsLike;
}
/**
* @brief get the temperature as an integer
* @return integer that is the current temperature
*/
int Weather::getTempFeelsLikeRounded() {
	return (int) std::round(this->tempFeelsLike);
}
/**
 * @brief get the location of weather
 * get the location of the weather. In our app, it should always be London, Ontario
 * @return location of weather as a string
 */
std::string Weather::getLocationName() {
	return this->locationName;
}
