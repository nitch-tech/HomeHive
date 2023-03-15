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
		double temperatureString;
		int conditionId;

	public:
		struct WeatherModel {
			int conditionId;
			std::string cityName;
			double temperature;
			const char temperatureString;
			std::string conditionName;

		};

		Weather();
		~Weather();
		int fetchWeatherData();
		double getTemp();
		int getTempRounded();
		int getCondId();
};


#endif //HOMEHIVE_WEATHER_H
