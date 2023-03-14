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
		GtkImage* imgBackground;

		GtkLabel* lblTime;
		GtkLabel* lblDate;
		GtkLabel* lblGreeting;
		GtkGrid* grid;
		GtkWidget* messageContainer;

		Unsplash* unsplash;
//		Timer* timer;

	public:
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setup() override;
		void show() override;
		void hide() override;
		void setDateAndTime(char* date, char* time);

		void setFullscreen(bool fullscreen);

		void changeBackgroundImage();
};


#endif //HOMEHIVE_HOMEVIEW_H
