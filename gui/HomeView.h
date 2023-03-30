//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
#include "../request/Unsplash.h"
#include "../request/weather.h"
//#include "../event/Timer.h"
#include "settings.h"
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
		GtkWidget* btnSettings;

		Unsplash* unsplash;
		// Timer* timer;
		Weather* weather;
		
	public:
		
		Settings* settings;
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();
		void clickedSettings(GtkWidget *widget, gpointer data);
		void setDateAndTime(char* date, char* time);
		void update_labels();
		void setFullscreen(bool fullscreen);
		
		void changeBackgroundImage();
		void updateWeather();

	protected:
		void setupLayout() override;
		void drawWidgets() override;
		
		void registerInteractivity() override;
};


#endif //HOMEHIVE_HOMEVIEW_H
