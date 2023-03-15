//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_UNSPLASHBACKGROUND_H
#define HOMEHIVE_UNSPLASHBACKGROUND_H


#include <string>

class UnsplashBackground {
	private:
		std::string id;
		int width;
		int height;
		std::string description;
		std::string url;

	public:
		explicit UnsplashBackground(std::string id);
		~UnsplashBackground();

		void setWidth(int width);
		void setHeight(int height);
		void setDescription(std::string desc);
		void setURL(std::string url);

		int getWidth();
		int getHeight();
		std::string getId();
		std::string getDescription();
		std::string getURL();
};


#endif //HOMEHIVE_UNSPLASHBACKGROUND_H
