//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_TIMER_H
#define HOMEHIVE_TIMER_H


#include <ctime>
#include <glib.h>
#include <glib/gprintf.h>
#include <functional>
#include "./IntervalView.h"

class Timer {
	private:
        IntervalView* view;
		std::time_t time;
		std::tm* tm;
		guint timerId;
		char* buffDate;
		char* buffTime;
		int ticks = 0;

	public:
		Timer(IntervalView* view);
		~Timer();
		void Register();
		void Unregister();

	private:
		static const gboolean onTimerTick(gpointer data);
};


#endif //HOMEHIVE_TIMER_H
