/*
 * @brief gui components for the news
 * @author Nathan Chan
 * Uses GTK to create a box conatiner and a label that is updated with headlines from the news class
 */
#include "NewsComponent.h"
#include "../GuiHelpers.h"


/*
 * @brief creates NewsComponent
 * news is an object of the news class
*/
NewsComponent::NewsComponent() {
	this->news = new News();
}

/*
 * @brief destroys news object
*/
NewsComponent::~NewsComponent() {
	delete this->news;
}

/*
 * @brief returns the news object
 * @return the news object
*/
News* NewsComponent::getNews() {
	return this->news;
}

/*
 * @brief sets up the box and label
 * create new GTK widgets box and label.
*/
void NewsComponent::setup() {
	// create news's box container
	GtkWidget* boxNews = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	this->container = (GtkBox*) boxNews;
	addClass(boxNews, "boxNews");

	// create the news label
	GtkWidget* lblNews = gtk_label_new_with_mnemonic("What's going on in the world?");
	this->lblNewsInfo = (GtkLabel*) lblNews;
	gtk_misc_set_alignment(GTK_MISC(lblNews), 0.5, 0.5);
	addClass(lblNews, "lblNews");
	gtk_box_pack_end(GTK_BOX(boxNews), lblNews, TRUE, TRUE, 0);
}

/*
 * @brief attaches the GTK components to the grid
*/
void NewsComponent::show() {
	gtk_grid_attach(this->parentGrid, (GtkWidget*) this->container, 0, 3, 1, 1);
}

/*
 * @brief updates the news displaying in the gui
 * @param fetchNews a boolean that is true when it is time to request more headlines and false when the next headline
 * is being grabbed from the list
 * if fetchNews is true, attempt to request new headlines from the news class, else get a headline from the news class.
 */
void NewsComponent::updateNews(bool fetchNews) {
	gchar *text;
	if (fetchNews){
		if (this->news->fetchNewsData() != 0) {
			text = g_strdup_printf("Failed to fetch news");
			gtk_label_set_text(this->lblNewsInfo, text);
			return;
		}
	}

	text = g_strdup_printf(
		"Your Top Stories Today\n%s",
		this->news->getHeadline().c_str()
	);
	gtk_label_set_text(this->lblNewsInfo, text);
}

void NewsComponent::settingsUpdated() {
}
