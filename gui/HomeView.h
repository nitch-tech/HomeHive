//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H


#include "BaseView.h"
#include "../request/Unsplash.h"
#include <sigc++-2.0/sigc++/sigc++.h>
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
		void updateNews(bool fetchNews);

		/**
		 * On Window Resize
		 *
		 * Whenever the window is resized, full screen, maximized, etc, this function will be called.
		 * The actual implementation is to resize the background image to fit the window size, and to
		 * resize the grid to fit the window size, to make it perfectly responsive.
		 *
		 * @param size The new window size structure
		 */
		void onWindowResize(GdkRectangle* size) override;

		/**
		 * Loads a new background image from a given file path
		 *
		 * @param fname The file path to load an image from
		 */
		void LoadBackgroundImage(std::string fname);

		/**
		 * Draws the background image, scaled to the window size
		 *
		 * @param width The window width
		 * @param height The window height
		 * @todo Look into gdk_pixbuf_scale(), to be able to use the offset, so the background
		 * can be centered to the window.
		 */
		void DrawBackgroundScaled(int width = 0, int height = 0);

	protected:
		void setupLayout() override;
		void drawWidgets() override;
		void registerInteractivity() override;

};


#endif //HOMEHIVE_HOMEVIEW_H
