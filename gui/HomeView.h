//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
#include "../request/Unsplash.h"
#include "../request/weather.h"
//#include "../event/Timer.h"
#include "Alarm.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>



class HomeView : public BaseView {
	private:
		GtkLayout* layout;
		GtkGrid* grid;
		GtkImage* imgBackground;
		GtkImage* imgWeather;

		GtkLabel* lblTime;
		GtkLabel* lblDate;
		GtkLabel* lblGreeting;
		GtkWidget* lblWeather;
		GtkWidget* dateTimeContainer;
        GtkWidget* hourSpin;
        GtkWidget* minuteSpin;
        GtkWidget* setAlarmButton;
		Unsplash* unsplash;
		Weather* weather;
        GtkWidget* calendar;
        GApplication* app;

        GDateTime* alarmTime;
    GDateTime* current_time;
    std::vector<Alarm*> alarms_;
    Alarm* alarm;




	public:


        static int* mintest;
		HomeView(GtkWindow* window);
        void on_activate (GApplication* app, gpointer data);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setDateAndTime(char* date, char* time);

		void setFullscreen(bool fullscreen);

		void changeBackgroundImage();
		void updateWeather();


        static void button_clicked_callback(GtkWidget *widget, gpointer user_data);
        void on_button_clicked(GtkWidget *widget, gpointer user_data);
        void checkAlarm();
        void isClicked();




protected:
		void setupLayout() override;
		void drawWidgets() override;
		void registerInteractivity() override;
};


#endif //HOMEHIVE_HOMEVIEW_H
