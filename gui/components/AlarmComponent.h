//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_ALARMCOMPONENT_H
#define HOMEHIVE_ALARMCOMPONENT_H

#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
//#include <AudioToolbox/AudioToolbox.h>
#include <SDL2/SDL.h>
#include "GuiComponent.h"
#include "../Alarm.h"

class AlarmComponent: public GuiComponent {
	private:
		GtkWidget* calendar;

		GtkWidget* hourSpin;
		GtkWidget* minuteSpin;
		GtkWidget* setAlarmButton;
		GDateTime* alarmTime;
		GDateTime* current_time;
		std::vector<Alarm*> alarms_;
		Alarm* alarm;
		GtkWidget* alarm_ok;
		GtkWidget* popup_window;

	public:
		AlarmComponent();
		static void button_clicked_callback(GtkWidget *widget, gpointer user_data);
		void on_button_clicked(GtkWidget *widget, gpointer user_data);
		static void ok_clicked_callback(GtkWidget *widget, gpointer user_data);
		void on_ok_button_clicked(GtkWidget *widget, gpointer user_data);

		int checkAlarm();// override;
		void isClicked();// override;

		void setup() override;
		void show() override;

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 *
		 * @todo Ability to change the datetime format
		 */
		void settingsUpdated() override;

};


#endif //HOMEHIVE_ALARMCOMPONENT_H
