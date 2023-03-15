//
// Created by mariam on 2023-03-14.
//
#include <string>
#include <nlohmann/json.hpp>
#include "weather.h"

using json = nlohmann::json;

const std::string WEATHER_API_ID = "6058560";
const std::string WEATHER_API_KEY = "7caf3dcfe4918513df6c3ddf1b564435";

Weather::Weather() {
	temperatureString = 0;
	conditionId = 0;
	this->locationName = "Unknown";
	this->tempFeelsLike = 0;
}

Weather::~Weather() = default;

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

double Weather::getTemp() {
	return temperatureString;
}

int Weather::getCondId() {
	return conditionId;
}

int Weather::getTempRounded() {
	return (int) std::round(this->temperatureString);
}

float Weather::getTempFeelsLike() {
	return this->tempFeelsLike;
}

int Weather::getTempFeelsLikeRounded() {
	return (int) std::round(this->tempFeelsLike);
}

std::string Weather::getLocationName() {
	return this->locationName;
}
