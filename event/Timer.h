//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_TIMER_H
#define HOMEHIVE_TIMER_H


#include <ctime>
#include <glib.h>
#include <glib/gprintf.h>
#include <functional>
#include "../gui/HomeView.h"

/**
 * Timer class, keeps track of the date time
 * @brief Timer class
 * @authors David, Nathan, Mariam
 */
class Timer {
	private:
		static Timer* instance;

		HomeView* view;
		std::time_t time;
		std::tm* tm;
		guint timerId;
		char* buffDate;
		char* buffTime;
		int ticks = 0;
		int backgroundInterval = 60*15;

		/**
		 * Timer constructor
		 * @brief Timer constructor
		 * @param view The home view instance
		 * @author David Tkachuk
		 */
		explicit Timer(HomeView* view);
		~Timer();

	public:
		/**
		 * Singleton instance, get timer instance or make new one
		 * @brief Get timer instance
		 * @param view The home view instance
		 * @author David Tkachuk
		 */
		static Timer* getInstance(HomeView* view);

		/**
		 * Register and start the timer
		 * @brief Register timer
		 * @author David Tkachuk
		 */
		void Register();

		/**
		 * Unregister and stop the timer
		 * @brief Unregister timer
		 * @author David Tkachuk
		 */
		void Unregister();

		/**
		 * Get the interval, in seconds, for how frequent the background changes.
		 * @return The interval, in seconds
		 * @author David Tkachuk
		 */
		int GetBackgroundInterval();

		/**
		 * Change the interval, in seconds, for how frequent the background changes.
		 * @param val The new interval, in seconds
		 * @authors David, Nick
		 */
		void SetBackgroundInterval(int val);

	private:
		/**
		 * Timer callback, called every second
		 * @brief Timer callback
		 * @param data The timer instance
		 * @return True
		 * @author David Tkachuk
		 */
		static const gboolean onTimerTick(gpointer data);
};


#endif //HOMEHIVE_TIMER_H
