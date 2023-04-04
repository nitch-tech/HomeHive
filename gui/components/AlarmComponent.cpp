//
// Created by dave on 03/04/23.
//

#include "AlarmComponent.h"
#include "../GuiHelpers.h"

AlarmComponent::AlarmComponent() {
	this->alarm = new Alarm();
}

void AlarmComponent::show() {

}

void AlarmComponent::setup() {
	// create alarm's box container
	GtkWidget* boxAlarm = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->parentGrid, boxAlarm, 0, 2, 1, 1);
	addClass(boxAlarm, "boxAlarm");

	setAlarmButton = gtk_button_new_with_label("Set Alarm");

	//Create calender widget, might delete later
	calendar = gtk_calendar_new();
	gtk_widget_set_name(calendar, "calendar");

	//Create the hour and minute button - hour ranges from 0 to 23, minutes range from 0 to 59
	hourSpin = gtk_spin_button_new_with_range(0, 23, 1);
	minuteSpin = gtk_spin_button_new_with_range(0, 59, 1);
	g_object_set_data(G_OBJECT(setAlarmButton), "minute_data", minuteSpin);
	g_object_set_data(G_OBJECT(setAlarmButton), "hour_data", hourSpin);

	//Add everything alarm related onto the screen - will be moved later onto settings pane
	gtk_box_pack_start(GTK_BOX(boxAlarm), hourSpin, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(boxAlarm), minuteSpin, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(boxAlarm), setAlarmButton, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(boxAlarm), calendar, FALSE, FALSE, 0);

	popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(popup_window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_default_size(GTK_WINDOW(popup_window), 400, 300);
	this->alarm_ok = gtk_button_new_with_label("OK");

	GtkWidget* label = gtk_label_new("Wake Up!");

	// Add the label to the window
	GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(box), label);
	gtk_container_add(GTK_CONTAINER(box), this->alarm_ok);

	gtk_container_add(GTK_CONTAINER(popup_window), box);
	// Show the window and box
	gtk_window_set_keep_above(GTK_WINDOW(popup_window), TRUE);
//	gtk_window_set_transient_for(GTK_WINDOW(popup_window), GTK_WINDOW(this->window));


	//callback function whenever the button gets clicked
	g_signal_connect(setAlarmButton, "clicked", G_CALLBACK(button_clicked_callback), this);
}


void AlarmComponent::button_clicked_callback(GtkWidget *widget, gpointer user_data) {
	AlarmComponent *obj = static_cast<AlarmComponent *>(user_data);
	//When the alarm button gets clicked, call this function
	obj->on_button_clicked(widget, user_data);


}
void AlarmComponent::ok_clicked_callback(GtkWidget *widget, gpointer user_data) {
	AlarmComponent *obj = static_cast<AlarmComponent *>(user_data);
	//When the alarm button gets clicked, call this function
	obj->on_ok_button_clicked(widget, user_data);


}
void AlarmComponent::on_ok_button_clicked(GtkWidget *widget, gpointer user_data) {

	//g_signal_handlers_disconnect_by_data(widget, user_data);
	//gtk_widget_destroy(popup_window);
	GtkWindow *window = GTK_WINDOW(user_data);
	GtkContainer *container = GTK_CONTAINER(gtk_widget_get_parent(GTK_WIDGET(window)));
	gtk_container_remove(container, GTK_WIDGET(window));
	gtk_widget_hide(GTK_WIDGET(window));

}

void AlarmComponent::on_button_clicked(GtkWidget *widget, gpointer user_data) {

	g_signal_handlers_disconnect_by_data(widget, user_data);

	//Set the current date and time for the alarm object - based on whatever numbers were displayed when the user clicked set alarm
	int alarmMin = gtk_spin_button_get_value_as_int(reinterpret_cast<GtkSpinButton *>(minuteSpin));
	this->alarm->setMinute(alarmMin);
	int alarmHour = gtk_spin_button_get_value_as_int(reinterpret_cast<GtkSpinButton *>(hourSpin));
	this->alarm->setHour(alarmHour);


	//Get the date of the alarm from the calendar widget when the user clicked the alarm
	guint year, month, day;
	gtk_calendar_get_date(GTK_CALENDAR(this->calendar), &year, &month, &day);

	//Create a GDateTime object for the set date and time
	this->alarmTime = g_date_time_new_local(year, month + 1, day, this->alarm->getHour(), this->alarm->getMinute(),0);
	g_print("Alarm set for %s\n", g_date_time_format(this->alarmTime, "%F %T"));



	//Get the current time
	this->current_time = g_date_time_new_now_local();

	//In order to makes sure that time alarm can go off at the set time, the seconds and the microseconds of the current time needs to be normalized
	gint64 microsec = g_date_time_get_microsecond(this->current_time);
	gint64 sec = g_date_time_to_unix(this->current_time);
	GDateTime *new_dt = g_date_time_new_from_unix_utc(sec);
	this->current_time = g_date_time_add_seconds(new_dt, microsec / G_USEC_PER_SEC);


	//Check if the alarm the user wants to set already exists. isPresent is 0, if the user has already set an alarm for that date and time.
	int isPresent = -2;
	//GDateTime *norm_dt2 = g_date_time_add_seconds(this->alarmTime, -g_date_time_get_second(this->alarmTime));
	for (const auto& alarm1 : alarms_) {
		isPresent = g_date_time_compare(alarm1->getAlarm(), this->alarmTime);
		if (isPresent == 0) {
			std::cerr<< "The alarm already exits " << std::endl;
			break;
		}
	}

	//If the alarm is not present,  push it onto the vector
	if (isPresent != 0 ) {
		alarm->setNewAlarm(this->alarmTime);
		alarms_.push_back(alarm);
	}
	this->checkAlarm();

}

int AlarmComponent::checkAlarm() {
	//loop through all alarms
	for (const auto& alarm : alarms_) {
		this->current_time = g_date_time_new_now_local();
		g_print("Current time %s\n", g_date_time_format(this->current_time, "%F %T"));

		//In order to makes sure that time alarm can go off at the set time, the seconds and the microseconds of the current time needs to be normalized
		gint64 microsec = g_date_time_get_microsecond(this->current_time);
		gint64 sec = g_date_time_to_unix(this->current_time);
		GDateTime *new_dt = g_date_time_new_from_unix_utc(sec);
		this->current_time = g_date_time_add_seconds(new_dt, microsec / G_USEC_PER_SEC);

		GDateTime *norm_dt1 = g_date_time_add_seconds(this->current_time, -g_date_time_get_second(this->current_time));
		g_print("Current time with normalized seconds %s\n", g_date_time_format(norm_dt1, "%F %T"));


		//Compares current time with the alarm time, return 0 if they're equal, meaning the alarm is going off
		int compare = g_date_time_compare(alarm->getAlarm(), norm_dt1);

		if (compare == -1) {
			std::cout << "You have entered a date that has already passed. It will be removed \n" <<std::endl;

		}else if (compare == 1) {
			std::cout << "Alarm has not gone off yet" << compare << "\n" << std::endl;}
		else if(compare == 0) {
			std::cout << "Alarm is going off \n" <<std::endl;

			if (SDL_Init(SDL_INIT_AUDIO) < 0) {
				std::cerr << "SDL_Init() error: " << SDL_GetError() << std::endl;
				return 1;
			}

			gtk_widget_show_all(popup_window);
			g_signal_connect(alarm_ok, "clicked", G_CALLBACK(ok_clicked_callback), popup_window);

			SDL_AudioSpec wavSpec;
			Uint8* wavBuffer;
			Uint32 wavLength;

			if (SDL_LoadWAV("../resources/s4-hilo.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
				std::cerr << "SDL_LoadWAV() error: " << SDL_GetError() << std::endl;
				return 1;
			}

			SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
			if (deviceId == 0) {
				std::cerr << "SDL_OpenAudioDevice() error: " << SDL_GetError() << std::endl;
				SDL_FreeWAV(wavBuffer);
				return 1;
			}

			if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) < 0) {
				std::cerr << "SDL_QueueAudio() error: " << SDL_GetError() << std::endl;
				SDL_CloseAudioDevice(deviceId);
				SDL_FreeWAV(wavBuffer);
				return 1;
			}

			SDL_PauseAudioDevice(deviceId, 0);

			SDL_Delay(500);

			SDL_CloseAudioDevice(deviceId);
			SDL_FreeWAV(wavBuffer);
			SDL_Quit();
		} }

}

void AlarmComponent::isClicked() {
}

void AlarmComponent::settingsUpdated() {
}
