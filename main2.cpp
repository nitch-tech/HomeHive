#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string>
#include <ctime>

typedef struct {
	GtkWidget *greeterlabel;
	GtkWidget *namelabel;
	GtkWidget *time;
	GtkWidget *nameentry;
	GtkWidget *enterbutton;
	GtkWidget *clearbutton;
} appWidgets;

/***************************************************************** PROTOTYPES */
void enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data);

void clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data);

void entry_callback(GtkWidget *widget, gpointer data);

/****************************************************************** CALLBACKS */
void enter_callback(GSimpleAction *action, GVariant *parameter, gpointer data) {
	const gchar *name;
	gchar str[50];
	appWidgets *wid = (appWidgets *) data;

	name = gtk_entry_get_text(GTK_ENTRY(wid->nameentry));
	g_sprintf(str, "Hello %s!", name);
	gtk_widget_override_font(wid->greeterlabel,
													 pango_font_description_from_string("Tahoma 20"));
	gtk_label_set_text(GTK_LABEL(wid->greeterlabel), (const gchar *) str);

	name = NULL;
	wid = NULL;
}

void clear_callback(GSimpleAction *action, GVariant *parameter, gpointer data) {
	appWidgets *wid = (appWidgets *) data;

	gtk_label_set_text(GTK_LABEL(wid->greeterlabel), "Greeter Demo");
	gtk_entry_set_text(GTK_ENTRY(wid->nameentry), "");

	wid = NULL;
}

void entry_callback(GtkWidget *widget, gpointer data) {
	enter_callback(NULL, NULL, data);
}

static int ttime = 0;

gboolean onTimerRun(gpointer data) {
	++ttime;
	std::time_t t = std::time(nullptr);
	std::tm *tm = std::localtime(&t);
	char st[69];
	std::sprintf(st, "%i:%i:%i\n%i-%i-%i", tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_year, tm->tm_mon, tm->tm_mday);
	GtkLabel *lbl = (GtkLabel *) data;
	gtk_label_set_text(lbl, st);
	return 1;
}

/***************************************************************** GUI THREAD */
static void
activate(GtkApplication *app, gpointer data) {
	GtkWidget *window;
	GtkWidget *vbox, *hbox;
	GtkWidget *headerbar;
	GtkStyleContext *context;

	appWidgets *wid = (appWidgets *) data;
	// map menu actions to callbacks
	const GActionEntry app_actions[] = {
					{"enter", enter_callback, NULL, NULL, NULL},
					{"clear", clear_callback, NULL, NULL, NULL}
	};

	// create a window with title, default size and icons
	window = gtk_application_window_new(app);
	gtk_window_set_application(GTK_WINDOW (window), GTK_APPLICATION (app));
	gtk_window_set_title(GTK_WINDOW(window), "GNOME Greeter Demo");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
	gtk_window_set_default_icon_from_file("icon.png", NULL);

	//gtk_window_fullscreen((GtkWindow*) window);
	gtk_window_maximize((GtkWindow *) window);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	// create label and entry
	wid->greeterlabel = gtk_label_new_with_mnemonic("Greeter Demo");
	gtk_widget_override_font(wid->greeterlabel,
													 pango_font_description_from_string("Tahoma 20"));
	gtk_widget_set_size_request(wid->greeterlabel, 0, 50);
	gtk_box_pack_start(GTK_BOX(vbox), wid->greeterlabel, FALSE, FALSE, 0);


	// create label and entry
	wid->time = gtk_label_new_with_mnemonic("00:00");
	gtk_widget_override_font(wid->time,
													 pango_font_description_from_string("Tahoma 20"));
	gtk_widget_set_size_request(wid->time, 0, 50);
	gtk_box_pack_start(GTK_BOX(vbox), wid->time, FALSE, FALSE, 0);
	gtk_label_set_text((GtkLabel *) wid->time, "eee");


	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	wid->namelabel = gtk_label_new_with_mnemonic("Name:");
	gtk_widget_set_size_request(wid->namelabel, 60, 40);
	gtk_box_pack_start(GTK_BOX(hbox), wid->namelabel, FALSE, FALSE, 0);
	wid->nameentry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(wid->nameentry), "Muster");
	gtk_box_pack_start(GTK_BOX(hbox), wid->nameentry, TRUE, TRUE, 0);
	g_signal_connect (G_OBJECT(wid->nameentry), "activate",
										G_CALLBACK(entry_callback), (gpointer) wid);

	// create a headerbar
	headerbar = gtk_header_bar_new();
	gtk_widget_show(headerbar);
	gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "GNOME Greeter");
	gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar),
															"A simple demo application");
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

	// create Clear button
	wid->clearbutton = gtk_button_new_with_label("Clear");
	gtk_actionable_set_action_name(GTK_ACTIONABLE(wid->clearbutton), "app.clear");
	context = gtk_widget_get_style_context(wid->clearbutton);
	gtk_style_context_add_class(context, "text-button");
	gtk_style_context_add_class(context, "destructive-action");
	gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), wid->clearbutton);

	// create Enter button
	wid->enterbutton = gtk_button_new_with_label("Enter");
	gtk_actionable_set_action_name(GTK_ACTIONABLE(wid->enterbutton), "app.enter");
	context = gtk_widget_get_style_context(wid->enterbutton);
	gtk_style_context_add_class(context, "text-button");
	gtk_style_context_add_class(context, "suggested-action");
	gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), wid->enterbutton);

	// connect actions with callbacks
	g_action_map_add_action_entries(G_ACTION_MAP (app), app_actions,
																	G_N_ELEMENTS (app_actions), wid);

	guint tmr = g_timeout_add(1000, onTimerRun, wid->time);

	gtk_widget_show_all(GTK_WIDGET(window));
}

/**************************************************************** MAIN THREAD */
int
main(int argc, char **argv) {
	GtkApplication *app;
	int status;
	appWidgets *wid = (appWidgets *) g_malloc(sizeof(appWidgets));

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer) wid);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	g_free(wid);
	wid = NULL;
	return status;
}