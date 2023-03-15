//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
#include "../request/Unsplash.h"
//#include "../event/Timer.h"

class HomeView : public BaseView {
	private:
		GtkLayout* layout;
		GtkGrid* grid;
		GtkImage* imgBackground;

		GtkLabel* lblTime;
		GtkLabel* lblDate;
		GtkLabel* lblGreeting;
		GtkLabel* lblWeather;
		GtkWidget* dateTimeContainer;

		Unsplash* unsplash;
//		Timer* timer;

	public:
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setDateAndTime(char* date, char* time);

		void setFullscreen(bool fullscreen);

		void changeBackgroundImage();

	protected:
		void setupLayout() override;
		void drawWidgets() override;
		void registerInteractivity() override;
};


#endif //HOMEHIVE_HOMEVIEW_H
