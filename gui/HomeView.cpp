//
// Created by dave on 13/03/23.
//

#include <iostream>
#include <cmath>
#include <gtk/gtk.h>
#include "HomeView.h"
#include "../event/Timer.h"

//#define DEBUG_GRID 1

/**
 * Size Allocator Signal Handler
 *
 * Whenever the window is resized, the grid is resized to match the window.
 *
 * @param widget The widget that fired the signal
 * @param allocation The new allocation of the widget (window dimemsions)
 * @param data Signal data (grid widget)
 */
static void onSizeAllocate(GtkWidget* widget, GdkRectangle* allocation, gpointer data) {
	GtkWidget* grid = (GtkWidget*) data;
	gtk_widget_set_size_request(grid, allocation->width, allocation->height);
}

/**
 * Add a custom CSS class name to some widget
 *
 * @param widget The widget to add the class to
 * @param className The CSS class name to add
 */
static void addClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, className.c_str());
}

/**
 * Remove a custom CSS class name from some widget
 *
 * @param widget The widget to remove the class from
 * @param className The CSS class name to remove
 */
static void removeClass(GtkWidget* widget, std::string className) {
	GtkStyleContext* context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, className.c_str());
}



HomeView::HomeView(GtkWindow *window) : BaseView(window) {
	this->unsplash = new Unsplash();
	this->weather = new Weather();
    this->alarm = new Alarm();
}

HomeView::~HomeView() {
	delete this->unsplash;
}

/**
 * Setup the view's layout and grid components
 */
void HomeView::setupLayout() {
	// create the base layout, which is the root widget container
	this->layout = (GtkLayout*) gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(this->window), (GtkWidget*) layout);
	gtk_widget_show((GtkWidget*) layout);

	#ifdef DEBUG_GRID
		addClass((GtkWidget*) layout, "debug");
	#endif

	// load & add the default background image, will be behind everything
	this->imgBackground = (GtkImage*) gtk_image_new_from_file("background.jpg");
	gtk_layout_put(layout, (GtkWidget*) imgBackground, 0, 0);

	// create a new grid, to position our UI elements
	auto gridWidget = gtk_grid_new();
	this->grid = (GtkGrid*) gridWidget;
	addClass(gridWidget, "grid");

	// force align the grid
	gtk_container_set_border_width(GTK_CONTAINER(this->layout), 0);
	gtk_widget_set_halign(gridWidget, GTK_ALIGN_FILL);
	gtk_widget_set_valign(gridWidget, GTK_ALIGN_FILL);

	// try to match the grid to the window's size, but do note this isn't enough
	// hence we need to register the size-allocate signal to dynamically make it responsive
	// to whenever the window is resized (or fullscreen)
	int width, height;
	gtk_window_get_size(GTK_WINDOW(window), &width, &height);
	gtk_widget_set_size_request(gridWidget, width, height);

	// force grid to expand to fill the window, but i haven't noticed this doing anything?
	// @TODO investigate this, maybe i'm going mad?
	gtk_widget_set_vexpand(gridWidget, true);
	gtk_widget_set_hexpand((GtkWidget*) this->grid, true);

	// add the grid to the layout
	gtk_layout_put(layout, (GtkWidget*) this->grid, 0, 0);
}

/**
 * Setup important HomeView functionality, such as signals and stylings
 */
void HomeView::registerInteractivity() {
	// register size-allocate signal to dynamically resize grid to window
	g_signal_connect(this->window, "size-allocate", G_CALLBACK(onSizeAllocate), this->grid);

	// create our timer, which does some background work frequently
	Timer* timer = new Timer(this);
	timer->Register();

	// load the CSS file, and set up styles
	auto provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "resources/homeview.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * Setup the HomeView's widgets
 */
void HomeView::drawWidgets() {
	// create a container for the date and time
	this->dateTimeContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(this->grid, this->dateTimeContainer, 0, 0, 1, 1);

	// create the time label
	GtkWidget* lblTime = gtk_label_new_with_mnemonic("00:00");
	this->lblTime = (GtkLabel*) lblTime;
	// gtk_widget_set_size_request(lblTime, 30, 50);
	addClass(lblTime, "lblTime");
	gtk_misc_set_alignment(GTK_MISC(lblTime), 0, 0); // allign left, there's no CSS property for this
	gtk_box_pack_start(GTK_BOX(this->dateTimeContainer), lblTime, FALSE, FALSE, 0);

	// create the date label
	GtkWidget* lblDate = gtk_label_new_with_mnemonic("May 69th 1969");
	this->lblDate = (GtkLabel*) lblDate;
	addClass(lblDate, "lblDate");
	gtk_misc_set_alignment(GTK_MISC(lblDate), 0, 0); // align left
	gtk_box_pack_start(GTK_BOX(this->dateTimeContainer), lblDate, FALSE, FALSE, 0);

	GtkWidget* topSeperator = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, topSeperator, 1, 0, 1, 1);
	gtk_widget_set_vexpand(topSeperator, true);
	gtk_widget_set_hexpand(topSeperator, true);
	addClass(topSeperator, "topSeperator");

	GtkWidget* midSeperator = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, midSeperator, 0, 1, 3, 2);
	gtk_widget_set_vexpand(midSeperator, true);
	gtk_widget_set_hexpand(midSeperator, true);
	addClass(midSeperator, "midSeperator");

	// create the greeting label
	GtkWidget* lblGreeting = gtk_label_new_with_mnemonic("Howdy, unknown user!");
	this->lblGreeting = (GtkLabel*) lblGreeting;
	addClass(lblGreeting, "lblGreeting");
	gtk_misc_set_alignment(GTK_MISC(lblGreeting), 1.0, 0.0);
	gtk_grid_attach(this->grid, lblGreeting, 2, 0, 1, 1);

	// create weather's box container
	GtkWidget* boxWeather = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(this->grid, boxWeather, 2, 3, 1, 1);
	addClass(boxWeather, "boxWeather");

	// create the weather label
	this->lblWeather = gtk_label_new_with_mnemonic("Finding the sun...");
	gtk_misc_set_alignment(GTK_MISC(lblWeather), 0.5, 0.5);
	addClass(lblWeather, "lblWeather");
	gtk_box_pack_end(GTK_BOX(boxWeather), lblWeather, TRUE, TRUE, 0);

	// create weather icon
	this->imgWeather = (GtkImage*) gtk_image_new();
	gtk_misc_set_alignment(GTK_MISC(imgWeather), 0.5, 0.5);
	gtk_box_pack_start(GTK_BOX(boxWeather), (GtkWidget*)imgWeather, FALSE, FALSE, 0);

    // create alarm's box container
    GtkWidget* boxAlarm = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach(this->grid, boxAlarm, 0, 3, 1, 1);
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



}

void HomeView::button_clicked_callback(GtkWidget *widget, gpointer user_data) {
    HomeView *obj = static_cast<HomeView *>(user_data);
    //When the alarm button gets clicked, call this function
    obj->on_button_clicked(widget, user_data);


}
void HomeView::on_button_clicked(GtkWidget *widget, gpointer user_data) {

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
    GDateTime *norm_dt2 = g_date_time_add_seconds(this->alarmTime, -g_date_time_get_second(this->alarmTime));
    for (const auto& alarm1 : alarms_) {
        isPresent = g_date_time_compare(alarm1->getAlarm(), norm_dt2);
        if (isPresent == 0) {
            std::cerr<< "The alarm already exits " << std::endl;
            break;
        }
    }

    //If the alarm is not present,  push it onto the vector
    if (isPresent != 0 ) {
        alarm->setNewAlarm(norm_dt2);
        alarms_.push_back(alarm);
    }
    this->checkAlarm();

}

int HomeView::checkAlarm() {
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


            GtkWidget* popup_window;
            popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_position(GTK_WINDOW(popup_window), GTK_WIN_POS_CENTER_ALWAYS);
            gtk_window_set_default_size(GTK_WINDOW(popup_window), 400, 300);

            GtkWidget* label = gtk_label_new("Wake Up!");

            // Add the label to the window
            gtk_container_add(GTK_CONTAINER(popup_window), label);
            // Show the window and box
            gtk_window_set_keep_above(GTK_WINDOW(popup_window), TRUE);
            gtk_window_set_transient_for(GTK_WINDOW(popup_window), GTK_WINDOW(this->window));

            gtk_widget_show_all(popup_window);



        } }



}

void HomeView::isClicked() {
    //callback function whenever the button gets clicked
    g_signal_connect(setAlarmButton, "clicked", G_CALLBACK(button_clicked_callback), this);


}

void HomeView::updateWeather() {
	gchar *text;
	if (this->weather->fetchWeatherData() != 0) {
		text = g_strdup_printf("Failed to fetch weather");
		gtk_label_set_text((GtkLabel*) this->lblWeather, text);
		return;
	} else {
		text = g_strdup_printf(
						"%s\nCurrently: %d°C | Feels Like: %i°C",
						this->weather->getLocationName().c_str(),
						this->weather->getTempRounded(),
						this->weather->getTempFeelsLikeRounded()
		);
		gtk_label_set_text((GtkLabel*) this->lblWeather, text);
	}

	std::string imagePath;
	int condId = this->weather->getCondId();
	if (condId >= 200 && condId <= 232) {
		imagePath = "resources/icons/cloud.bolt.png";
	} else if (condId >= 300 && condId <= 321) {
		imagePath = "resources/icons/cloud.drizzle.png";
	} else if (condId >= 500 && condId <= 531) {
		imagePath = "resources/icons/cloud.drizzle.png";
	} else if (condId >= 600 && condId <= 622) {
		imagePath = "resources/icons/cloud.snow.png";
	} else if (condId >= 701 && condId <= 781) {
		imagePath = "resources/icons/sun.max.png";
	} else if (condId == 800) {
		imagePath = "resources/icons/cloud.drizzle.png";
	} else if (condId >= 801 && condId <= 804) {
		imagePath = "resources/icons/cloud.png";
	} else {
		imagePath = "resources/icons/cloud.png";
	}

	// resize image  pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(imagePath.c_str(), NULL);
	GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, 96, 96, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgWeather), scaled);
}

void HomeView::setDateAndTime(char *date, char *time) {
	gtk_label_set_text(this->lblDate, date);
	gtk_label_set_text(this->lblTime, time);
}

void HomeView::changeBackgroundImage() {
	// fetch a random background from unsplash API
	auto bg = this->unsplash->getRandomBackground();
	if (bg == nullptr) {
		return;
	}

	// try to download the background
	if (!this->unsplash->downloadBackground(bg, 1920, 1080)) {
		return;
	}

	// reload the background image
	gtk_image_set_from_file(this->imgBackground, this->unsplash->getBackgroundImage().c_str());

	// refresh and reload background
	gtk_widget_queue_draw((GtkWidget*) this->imgBackground);
	gtk_widget_show((GtkWidget*) this->imgBackground);
}

void HomeView::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		gtk_window_fullscreen(this->window);
	} else {
		gtk_window_unfullscreen(this->window);
	}
}


