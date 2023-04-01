//
// Created by Nathan on 2023-03-30.
//
#include <string>
#include <vector>
#include "news.h"

News::News() {
	std::vector<std::string> newsList;
    this->story = 0;
}

News::~News() = default;

int News::fetchNewsData() {
    Request initial("https://www.reddit.com/r/news.rss");

    if (initial.execute()) {
		std::string res = initial.getResponse();
        std::regex word_regex("<title>.{100}");
            auto words_begin = 
                std::sregex_iterator(res.begin(), res.end(), word_regex);
            auto words_end = std::sregex_iterator();


        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string match_str = match.str();
            match_str.erase(0, 7);
            std::string headline;
            int j = 0;
            while(match_str[j] != '<' && j < match_str.length()){
                headline.push_back(match_str[j]);
                j++;
            }

            if(match_str[j] != '<') {
                headline.append("...");
            }
            
            if(headline != "News") {
                this->newsList.push_back(headline);
            }
        }

		return 0;

	} else {
		std::cerr << "API request returned NULL" << std::endl;
		return -1;
	}

}

std::string News::getHeadline() {
    int item = this->story%this->newsList.size();
    this->story++;
    return this->newsList[item];
}