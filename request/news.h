/*
 * @brief header file for news class
 * @author Nathan Chan
*/

#ifndef HOMEHIVE_NEWS_H
#define HOMEHIVE_NEWS_H

#include <string>
#include <vector>
#include <regex>
#include <vector>
#include <iostream>
#include "request.h"


class News {
	private:
        std::vector<std::string> newsList; 	// vector containing headlines represented by a string
		int story;							// int tracking the number of stories

	public:
		News();								// constructor
		~News();							// destructor
		int fetchNewsData();				// fetches the news headlines from reddit
		std::string getHeadline();			// returns a headline string
};


#endif //HOMEHIVE_NEWS_H
