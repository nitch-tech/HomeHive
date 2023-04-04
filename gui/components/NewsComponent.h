/*
 * @file NewsComponent.h
 * @brief headerfile for NewsComponent class
 * @author Nathan Chan
*/

#ifndef HOMEHIVE_NEWSCOMPONENT_H
#define HOMEHIVE_NEWSCOMPONENT_H

#include <gtk/gtk.h>
#include "GuiComponent.h"
#include "../../request/news.h"

/*
 * @class NewsComponent
 * @brief manages the gui for the news headlines 
*/
class NewsComponent: public GuiComponent {
	private:
		//GtkLabel* lblNewsTitle;

		//GtkLabel* lblNewsInfo;	

		News* news; 						// news object to get headlines from

	public:
		NewsComponent();
		~NewsComponent();

		/*
		 * @brief returns the news object
		 * @return the news object
		*/
		News* getNews();	

		/*
		 * @brief sets up the box and label
		 * create new GTK widgets box and label.
		*/
		void setup() override;

		/*
		 * @brief attaches the GTK components to the grid
		*/
		void show() override;

		void settingsUpdated() override;

		/*
		 * @brief updates the news displaying in the gui
		 * @param fetchNews a boolean that is true when it is time to request more headlines and false when the next headline
		 * is being grabbed from the list
		 * 
		*/
		void updateNews(bool fetchNews);
};


#endif //HOMEHIVE_NEWSCOMPONENT_H
