//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
#include "../request/Unsplash.h"
#include <sigc++-2.0/sigc++/sigc++.h>
#include "../request/weather.h"
//#include "../event/Timer.h"

class HomeView : public BaseView {
	private:
		GtkLayout* layout;
	public: GtkGrid* grid;
		GtkImage* imgBackground;
		GtkImage* imgWeather;

		GtkLabel* lblTime;
		GtkLabel* lblDate;
		GtkLabel* lblGreeting;
		GtkWidget* lblWeather;
		GtkWidget* dateTimeContainer;

		Unsplash* unsplash;
		// Timer* timer;
		Weather* weather;

	public:
		GdkPixbuf* bgBuff;
		GdkPixbuf* bgBuffScaled;

	public:
		HomeView(GtkWindow* window);
		// BaseView(App* app, GtkWindow* window);
		~HomeView();

		void setDateAndTime(char* date, char* time);

		void setFullscreen(bool fullscreen);

		void changeBackgroundImage();
		void updateWeather();

		void onWindowResize(GdkRectangle* size) override;

		void LoadBackgroundImage(std::string fname);
		void DrawBackgroundScaled(int width = 0, int height = 0);

	protected:
		void setupLayout() override;
		void drawWidgets() override;
		void registerInteractivity() override;

};


#endif //HOMEHIVE_HOMEVIEW_H
