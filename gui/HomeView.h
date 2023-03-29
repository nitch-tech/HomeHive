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
        Alarm alarm;

	public:
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setDateAndTime(char* date, char* time);

		void setFullscreen(bool fullscreen);

		void changeBackgroundImage();
		void updateWeather();

        void setAlarm();
        static gboolean button_press_event ( GtkWidget *widget, GdkEvent *event );




protected:
		void setupLayout() override;
		void drawWidgets() override;
		void registerInteractivity() override;
};


#endif //HOMEHIVE_HOMEVIEW_H
