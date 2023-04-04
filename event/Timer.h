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

		explicit Timer(HomeView* view);
		~Timer();

	public:
		static Timer* getInstance(HomeView* view);

		void Register();
		void Unregister();

		/**
		 * Get the interval, in seconds, for how frequent the background changes.
		 * @return The interval, in seconds
		 */
		int GetBackgroundInterval();

		/**
		 * Change the interval, in seconds, for how frequent the background changes.
		 * @param val The new interval, in seconds
		 */
		void SetBackgroundInterval(int val);

	private:
		static const gboolean onTimerTick(gpointer data);
};


#endif //HOMEHIVE_TIMER_H
