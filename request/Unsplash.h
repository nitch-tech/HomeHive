//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_UNSPLASH_H
#define HOMEHIVE_UNSPLASH_H


#include "UnsplashBackground.h"
#include "request.h"

class Unsplash {
	public:
		Unsplash();
		~Unsplash();

		UnsplashBackground* getRandomBackground();
};


#endif //HOMEHIVE_UNSPLASH_H
