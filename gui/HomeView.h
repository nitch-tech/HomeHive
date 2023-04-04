//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_HOMEVIEW_H
#define HOMEHIVE_HOMEVIEW_H

#include "BaseView.h"
#include "../request/Unsplash.h"
#include "../request/weather.h"
#include "../request/news.h"
#include "settings.h"
#include "components/GuiComponent.h"
#include "components/DateTimeComponent.h"
#include "components/WeatherComponent.h"
#include "components/NewsComponent.h"
#include "components/AlarmComponent.h"
//#include "../event/IntervalView.h"


class HomeView : public BaseView { // };, public IntervalView {
	private:
		GSettings* settings;

		std::vector<GuiComponent*> components;
		DateTimeComponent* dateTimeComponent;
		WeatherComponent* weatherComponent;
		NewsComponent* newsComponent;
		AlarmComponent* alarmComponent;

		GtkLayout* layout;
		GtkGrid* grid;
		GtkImage* imgBackground;

		GtkLabel* lblGreeting;

		Unsplash* unsplash;

		GdkPixbuf* bgBuff;
		GdkPixbuf* bgBuffScaled;

	public:
		HomeView(GtkWindow* window, GSettings* settings);
		~HomeView();

		/**
		 * Update the view, something (ie: a setting) was changed, so
		* triggger various components to update themselves.
		*/
		void update() override;
		void setFullscreen(bool fullscreen);

		/**
		 * Retrieves the DateTimeComponent instance, which contains and manages
		 * the date and time widgets on screen.
		 *
		 * @return The current DateTimeComponent instance
		 */
		DateTimeComponent* getDateTimeComponent();

		/**
		 * Retrieves the WeatherComponent instance, which handles retrieving and rendering
		 * information about the current weather.
		 *
		 * @return The current WeatherComponent instance
		 */
		WeatherComponent* getWeatherComponent();

		/**
		 * Retrieves the NewsComponent instance, which handles retrieving and rendering
		 * information about the current news.
		 *
		 * @return The current NewsComponent instance
		 */
		NewsComponent* getNewsComponent();

		/**
		 * Retrieves the AlarmComponent instance, which handles retrieving and rendering
		 * information about the current alarms.
		 *
		 * @return The current AlarmComponent instance
		 */
		AlarmComponent* getAlarmComponent();

		void changeBackgroundImage();

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

	private:
		/**
		 * Add an empty box widget to the grid, which is used to seperate
		 * all the UI widgets within the entire grid to align them.
		 *
		 * @param id The ID of the widget
		 * @param left The left position of the widget in the grid
		 * @param top The top position of the widget in the grid
		 * @param width The width of the widget in the grid
		 * @param height The height of the widget in the grid
		 */
		void addSeperator(const std::string id, int left, int top, int width, int height);


	protected:
		void setupLayout() override;
		void drawWidgets() override;

		void registerInteractivity() override;

};


#endif //HOMEHIVE_HOMEVIEW_H
