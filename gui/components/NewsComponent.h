//
// Created by dave on 03/04/23.
//

#ifndef HOMEHIVE_NEWSCOMPONENT_H
#define HOMEHIVE_NEWSCOMPONENT_H

#include <gtk/gtk.h>
#include "GuiComponent.h"
#include "../../request/news.h"

class NewsComponent: public GuiComponent {
	private:
		//GtkLabel* lblNewsTitle;
		GtkLabel* lblNewsInfo;
		News* news;

	public:
		NewsComponent();
		~NewsComponent();

		News* getNews();

		void setup() override;
		void show() override;
		void hide() override;

		void updateNews(bool fetchNews);
};


#endif //HOMEHIVE_NEWSCOMPONENT_H
