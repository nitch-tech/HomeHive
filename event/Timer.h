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
		HomeView* view;
		std::time_t time;
		std::tm* tm;
		guint timerId;
		char* buffDate;
		char* buffTime;
		int ticks = 0;
		bool fetchNews = TRUE;
//		const std::function<void(char*,char*)>& callback;

	public:
//		Timer(const std::function<void(char *, char *)> &callback);
		Timer(HomeView* view);
		~Timer();
		void Register();
		void Unregister();
		void SetBackInterval(int set);
	private:
		static const gboolean onTimerTick(gpointer data);
};


#endif //HOMEHIVE_TIMER_H
