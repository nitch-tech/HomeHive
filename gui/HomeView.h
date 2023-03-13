//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
//#include "../event/Timer.h"

class HomeView : public BaseView {
	private:
		GtkLabel* lblTime;
		GtkLabel* lblDate;
		GtkLabel* lblGreeting;
		GtkTable* grid;
		GtkWidget* messageContainer;
//		Timer* timer;

	public:
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setup() override;
		void show() override;
		void hide() override;
		void setDateAndTime(char* date, char* time);
};


#endif //HOMEHIVE_HOMEVIEW_H
