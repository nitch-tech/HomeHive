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

		/**
		 * Update the component
		 *
		 * When executed, and if required, this component may update or re-render
		 * itself to reflect any changes in the application settings.
		 *
		 * @todo ability to change the news source
		 */
		void settingsUpdated() override;

		void updateNews(bool fetchNews);
};


#endif //HOMEHIVE_NEWSCOMPONENT_H
