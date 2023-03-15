//
// Created by mariam on 2023-03-14.
//


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
		Weather();
		~Weather();
		int fetchWeatherData();
		double getTemp();
		int getTempRounded();
		std::string getLocationName();
		float getTempFeelsLike();
		int getTempFeelsLikeRounded();
		int getCondId();
};


#endif //HOMEHIVE_WEATHER_H
