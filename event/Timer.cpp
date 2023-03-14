//
// Created by dave on 13/03/23.
//

#include <string>
#include "Timer.h"

int BACKGROUND_INTERVAL = 15 * 60; // every 15 minutes

//Timer::Timer(const std::function<void(char *, char *)> &cb)
//				: callback(cb) {
Timer::Timer(HomeView* v) {
	this->view = v;
	this->buffDate = (char*)malloc(sizeof(char)*69);
	this->buffTime = (char*)malloc(sizeof(char)*69);
}

Timer::~Timer() {
}

void Timer::Register() {
	// nifty lil hack, run the timer callback FIRST to populate the time before scheduling the timer
	Timer::onTimerTick(this);
	this->timerId = g_timeout_add(1000, (GSourceFunc) Timer::onTimerTick, (gpointer) this);
}

void Timer::Unregister() {
}

const gboolean Timer::onTimerTick(gpointer data) {
	Timer* tmr = (Timer*) data;
	tmr->time = std::time(nullptr);
	tmr->tm = std::localtime(&tmr->time);


//	std::sprintf(tmr->buffTime, "%02d:%02d:%02d", tmr->tm->tm_hour, tmr->tm->tm_min, tmr->tm->tm_sec);
//	std::sprintf(tmr->buffDate, "%i-%i-%i", tmr->tm->tm_year, tmr->tm->tm_mon, tmr->tm->tm_mday);

	// there's built in string datetime formatting with better formatting omg!!! :DD
	strftime(tmr->buffTime, 69, "%H:%M:%S %p", tmr->tm);
	strftime(tmr->buffDate, 69, "%a, %B %d, %Y", tmr->tm);

//	(tmr->callback)(tmr->buffDate, tmr->buffTime);
	tmr->view->setDateAndTime(tmr->buffDate, tmr->buffTime);

	if ((tmr->ticks % BACKGROUND_INTERVAL) == 0) {
		tmr->view->changeBackgroundImage();
	}
	++tmr->ticks;

	return 1;
}
