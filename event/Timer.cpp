//
// Created by dave on 13/03/23.
//

#include <string>
#include "Timer.h"

const int WEATHER_INTERVAL = 5 * 60; // every 5 minutes
const int NEWS_INTERVAL = 30; // every 30 seconds
const int NEWS_FETCH_INTERVAL = 30 * 60; // every 1 minute
const int ALARM_INTERVAL = 60;// every minute

Timer* Timer::instance = nullptr;

Timer *Timer::getInstance(HomeView *view) {
	if (Timer::instance == nullptr) {
		Timer::instance = new Timer(view);
	}
	return Timer::instance;
}

Timer::Timer(HomeView* v) {
	this->view = v;
	this->buffDate = (char*)malloc(sizeof(char)*69);
	this->buffTime = (char*)malloc(sizeof(char)*69);
}

Timer::~Timer() {
	this->Unregister();
	delete this->buffDate;
	delete this->buffTime;
}

/**
 * Change the interval, in seconds, for how frequent the background changes.
 * @param val The new interval, in seconds
 */
void Timer::SetBackgroundInterval(int val) {
	this->backgroundInterval = val;
}

/**
 * Get the interval, in seconds, for how frequent the background changes.
 * @return The interval, in seconds
 */
int Timer::GetBackgroundInterval() {
	return this->backgroundInterval;
}

void Timer::Register() {
	// nifty lil hack, run the timer callback FIRST to populate the time before scheduling the timer
	Timer::onTimerTick(this);
	this->timerId = g_timeout_add(1000, (GSourceFunc) Timer::onTimerTick, (gpointer) this);
}

void Timer::Unregister() {
	g_source_remove(this->timerId);
}

const gboolean Timer::onTimerTick(gpointer data) {
	Timer* tmr = (Timer*) data;
	tmr->time = std::time(nullptr);
	tmr->tm = std::localtime(&tmr->time);

	// nifty ctime's format to strings, see: http://www.cplusplus.com/reference/ctime/strftime/ for all flags
	strftime(tmr->buffTime, 69, "%H:%M:%S %p", tmr->tm);
	strftime(tmr->buffDate, 69, "%a, %B %d, %Y", tmr->tm);

//	(tmr->callback)(tmr->buffDate, tmr->buffTime);
	tmr->view->getDateTimeComponent()->setDateAndTime(tmr->buffDate, tmr->buffTime);

	// update background
	if ((tmr->ticks % tmr->GetBackgroundInterval()) == 0) {
		tmr->view->changeBackgroundImage();
	}

	// update weather
	if ((tmr->ticks % WEATHER_INTERVAL) == 0) {
		tmr->view->getWeatherComponent()->updateWeather();
	}

	// refresh headline and attempt to fetch latest news
	if((tmr->ticks % NEWS_INTERVAL) == 0) {
		tmr->view->getNewsComponent()->updateNews((tmr->ticks % NEWS_FETCH_INTERVAL) == 0);
	}

	// check alarm
	if ((tmr->ticks % ALARM_INTERVAL) == 0) {
			tmr->view->getAlarmComponent()->checkAlarm();
	}
/*	if ((tmr->ticks % 1) == 0) {
		tmr->view->isClicked();
	}*/

	++tmr->ticks;
	return true;
}
