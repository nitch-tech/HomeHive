//
// Created by Nathan on 2023-03-30.
//

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
        std::vector<std::string> newsList;
		int story;

	public:
		News();
		~News();
        int fetchNewsData();
        std::string getHeadline();
};


#endif //HOMEHIVE_NEWS_H
