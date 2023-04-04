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

/**
 * The HomeView class is the main view of the application, and is responsible for
 * rendering the main screen of the application.
 * @brief The main view of the application
 * @author Nick, Nathan, David, Marian
 */
class HomeView : public BaseView {
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

		/**
		 * HomeView constructor
		 *
		 * @brief HomeView constructor
		 * @param window GTK window instance (what to render in)
		 * @param settings GTK Settings instance (access/modify settings)
		 * @author David Tkachuk
		 */
		HomeView(GtkWindow* window, GSettings* settings);
		~HomeView();

		/**
		 * Update the view, something (ie: a setting) was changed, so triggger various components to update themselves.
		 * @brief Update the view after settings changed
		 * @author David Tkachuk
		 */
		void update() override;

		/**
		 * Makes the window fullscreen
		 * @brief Makes the window fullscreen
		 * @param fullscreen True for fullscreen mode, false for windowed mode
		 * @author David Tkachuk
		 */
		void setFullscreen(bool fullscreen);

		/**
		 * Retrieves the DateTimeComponent instance, which contains and manages
		 * the date and time widgets on screen.
		 *
		 * @brief Retrieves the DateTimeComponent instance
		 * @author David Tkachuk
		 * @return The current DateTimeComponent instance
		 */
		DateTimeComponent* getDateTimeComponent();

		/**
		 * Retrieves the WeatherComponent instance, which handles retrieving and rendering
		 * information about the current weather.
		 *
		 * @return The current WeatherComponent instance
		 * @author David Tkachuk
		 * @brief Retrieves the WeatherComponent instance
		 */
		WeatherComponent* getWeatherComponent();

		/**
		 * Retrieves the NewsComponent instance, which handles retrieving and rendering
		 * information about the current news.
		 *
		 * @return The current NewsComponent instance
		 * @brief Retrieves the NewsComponent instance
		 * @author David Tkachuk
		 */
		NewsComponent* getNewsComponent();

		/**
		 * Retrieves the AlarmComponent instance, which handles retrieving and rendering
		 * information about the current alarms.
		 *
		 * @return The current AlarmComponent instance
		 * @brief Retrieves the AlarmComponent instance
		 * @author David Tkachuk
		 */
		AlarmComponent* getAlarmComponent();

		/**
		 * Retrieve a new background image from unsplash and then load it.
		 * @brief Load new background image
		 * @author David Tkachuk
		 */
		void changeBackgroundImage();

		/**
		 * On Window Resize
		 *
		 * Whenever the window is resized, full screen, maximized, etc, this function will be called.
		 * The actual implementation is to resize the background image to fit the window size, and to
		 * resize the grid to fit the window size, to make it perfectly responsive.
		 *
		 * @param size The new window size structure
		 * @brief Window Resize Event Handler for adaptive windows
		 * @author David Tkachuk
		 */
		void onWindowResize(GdkRectangle* size) override;

		/**
		 * Loads a new background image from a given file path
		 *
		 * @param fname The file path to load an image from
		 * @brief Loads a new background image from a given file path
		 */
		void LoadBackgroundImage(std::string fname);

		/**
		 * Draws the background image, scaled to the window size
		 *
		 * @param width The window width
		 * @param height The window height
		 * @brief Draw background image to window
		 * @author David Tkachuk
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
		 * @brief Add an empty box widget to the grid
		 * @author David Tkachuk
		 */
		void addSeperator(const std::string id, int left, int top, int width, int height);


	protected:
		/**
		 * Setup the layout of the view, this is called when the view is first created, and is used to
		 * setup the basic structure/grid and how widgets should be placed.
		 * @brief Setup the layout of the view
		 * @author David Tkachuk
		 */
		void setupLayout() override;

		/**
		 * Draw all widgets in the view, rendering them to the window.
		 * @brief Draw all widgets in the view
		 * @author David Tkachuk
		 */
		void drawWidgets() override;

		/**
		 * Register interactivity and signals/events for all widgets in the view, and setup
		 * the CSS stylesheets.
		 * @brief Register interactivity & events
		 * @author David Tkachuk
		 */
		void registerInteractivity() override;

};


#endif //HOMEHIVE_HOMEVIEW_H
