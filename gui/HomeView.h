//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
#include "../request/Unsplash.h"
#include "../request/weather.h"
#include "../request/news.h"
//#include "../event/Timer.h"

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
		GtkWidget* lblNews;
		GtkWidget* dateTimeContainer;

		Unsplash* unsplash;
		// Timer* timer;
		Weather* weather;
		News* news;

	public:
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setDateAndTime(char* date, char* time);

		void setFullscreen(bool fullscreen);

		void changeBackgroundImage();
		void updateWeather();
		void updateNews(bool fetchNews);

	protected:
		void setupLayout() override;
		void drawWidgets() override;
		void registerInteractivity() override;
};


#endif //HOMEHIVE_HOMEVIEW_H
