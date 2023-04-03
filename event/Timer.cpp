//
// Created by dave on 13/03/23.
//

#include <string>
#include "Timer.h"

int BACKGROUND_INTERVAL = 15 * 60; // every 15 minutes
const int WEATHER_INTERVAL = 5 * 60; // every 5 minutes
const int NEWS_INTERVAL = 30; // every 30 seconds
const int NEWS_FETCH_INTERVAL = 30 * 60; // every 1 minute 

//Timer::Timer(const std::function<void(char *, char *)> &cb)
//				: callback(cb) {
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
void Timer::SetBackInterval(int set){
	BACKGROUND_INTERVAL = set;
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
	if ((tmr->ticks % BACKGROUND_INTERVAL) == 0) {
		tmr->view->changeBackgroundImage();
	}

	// update weather
	if ((tmr->ticks % WEATHER_INTERVAL) == 0) {
		tmr->view->updateWeather();
	}

	// does news need to be fetched
	if((tmr->ticks % NEWS_FETCH_INTERVAL) == 0) {
		tmr->fetchNews = TRUE;
	} else {
		tmr->fetchNews = FALSE;
	}

	// refresh headline
	if((tmr->ticks % NEWS_INTERVAL) == 0) {
		tmr->view->updateNews(tmr->fetchNews);
	}
	++tmr->ticks;
	return true;
}
