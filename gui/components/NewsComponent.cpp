#include "NewsComponent.h"
#include "../GuiHelpers.h"

NewsComponent::NewsComponent() {
	this->news = new News();
}

NewsComponent::~NewsComponent() {
	delete this->news;
}

News* NewsComponent::getNews() {
	return this->news;
}

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

void NewsComponent::show() {
	gtk_grid_attach(this->parentGrid, (GtkWidget*) this->container, 0, 3, 1, 1);
}

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
