//
// Created by mariam on 2023-03-14.
//
#include <string>
#include "weather.h"




Weather::Weather() {

}

int Weather::fetchWeatherData() {
    /*
https://api.openweathermap.org/data/2.5/weather?id=6058560&appid=7caf3dcfe4918513df6c3ddf1b564435&units=metric
*/

    curl_global_init(CURL_GLOBAL_ALL);
    Request initial("https://api.openweathermap.org/data/2.5/weather?id=6058560&appid=7caf3dcfe4918513df6c3ddf1b564435&units=metric");

    initial.execute();

    char* test = initial.result();

    if (test != NULL) {
        json data = json::parse(test);

        // access fields

        json& o = data["main"];
        json& gi = o["temp"];
        for (json& weather : data["weather"]) {
            conditionId = weather["id"];

        }






        temperatureString = gi;

        std::cout <<gi<<"     "<<temperatureString <<"\n" ;
        std::cout <<gi<<"   the cond id  "<<conditionId <<"\n" ;
        return 0;

    }else  {
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