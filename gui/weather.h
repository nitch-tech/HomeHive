//
// Created by mariam on 2023-03-14.
//


#ifndef HOMEHIVE_WEATHER_H
#define HOMEHIVE_WEATHER_H


#include <iostream>
#include <fstream>
#include <string>
#include "curl/curl.h"
#include "../request/request.h"

#include <stdlib.h>

using std::cout;
using std::endl;

class Weather {

private:
    double temperatureString;
    int conditionId;



public:
    struct WeatherModel{
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
    int getCondId();
};





#endif //HOMEHIVE_WEATHER_H
