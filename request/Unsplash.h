//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_UNSPLASH_H
#define HOMEHIVE_UNSPLASH_H


#include <map>
#include "UnsplashBackground.h"
#include "request.h"

class Unsplash {
	private:
		FILE* file;
		bool isBufferImage = false;
		std::map<std::string, std::string> categories;
		std::string currentCategoryId;

	public:
		Unsplash();
		~Unsplash();

		UnsplashBackground* getRandomBackground();
		bool downloadBackground(UnsplashBackground* background, int width = 0, int height = 0);

		std::string getBackgroundImage();
		std::map<std::string, std::string> getCategories();
		std::string getCurrentCategoryId();
		std::string getCurrentCategoryName();
		std::string getCategoryName(std::string id);

	private:
		void loadCategories();
};


#endif //HOMEHIVE_UNSPLASH_H
