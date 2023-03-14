//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_UNSPLASH_H
#define HOMEHIVE_UNSPLASH_H


#include "UnsplashBackground.h"
#include "request.h"

class Unsplash {
	private:
		FILE* file;
		bool isBufferImage = false;

	public:
		Unsplash();
		~Unsplash();

		UnsplashBackground* getRandomBackground();
		bool downloadBackground(UnsplashBackground* background, int width = 0, int height = 0);

		std::string getBackgroundImage();
};


#endif //HOMEHIVE_UNSPLASH_H
