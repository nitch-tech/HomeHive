/*
 * @brief Grabs news headlines 
 * @author Nathan Chan
 * This class uses the request class to get data from the uplifting news subreddit.
 * The data from this request is parsed and added to a vector that conatins all of the news headlines
*/
#include <string>
#include <vector>
#include "news.h"

/*
 * @brief news constructor
 * Creates an empty vector to hold news headlines and the initializes the number of stories to zero.
 * The number of stories is tracked so that all of the stories can be looped through.
*/
News::News() {
	std::vector<std::string> newsList;
    this->story = 0;
}

/*
 * Destructor
*/
News::~News() = default;

/*
 * @brief fetch the news headlines
 * @return 0 on success and 1 on failure
 * Use regex to find the first 100 characters in the title. If the title is longer than 100 characters, use '...' to 
 * indicate this. Clean up the output and add it to the vector list.
*/
int News::fetchNewsData() {
    Request initial("https://www.reddit.com/r/UpliftingNews/.rss");

    if (initial.execute()) {
		std::string res = initial.getResponse();
        std::regex word_regex("<title>.{100}");
            auto words_begin = 
                std::sregex_iterator(res.begin(), res.end(), word_regex);
            auto words_end = std::sregex_iterator();


        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string match_str = match.str();
            match_str.erase(0, 7);  // erase title tag
            std::string headline;
            int j = 0;
            while(match_str[j] != '<' && j < match_str.length()){
                headline.push_back(match_str[j]);
                j++;
            }

            if(match_str[j] != '<') {
                headline.append("...");
            }
            
            if(headline != "Uplifting News") { // erase subreddit title
                this->newsList.push_back(headline);
            }
        }

		return 0;

	} else {
		std::cerr << "API request returned NULL" << std::endl;
		return -1;
	}

}

/*
 * @brief get a headline from the vector
 * @return a string containing a news headline
 * Each time the method is called, it returns the next story in the vector.
*/
std::string News::getHeadline() {
    int item = this->story%this->newsList.size();
    this->story++;
    return this->newsList[item];
}