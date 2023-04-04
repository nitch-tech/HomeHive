//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_UNSPLASH_H
#define HOMEHIVE_UNSPLASH_H


#include <map>
#include "UnsplashBackground.h"
#include "request.h"

/**
 * Unsplash background manager class
 *
 * Does some magic where it'll request a random background of a given category
 * and then fetch the file to a load file, and will instruct home view
 * to laod the new image.
 *
 * @author David Tkachuk
 * @brief Unsplash background manager class
 */
class Unsplash {
	private:
		FILE* file;
		std::map<std::string, std::string> categories;
		std::string currentCategoryId;
		bool isBufferImage = false;

	public:
	/**
	 * Unsplash class constructor
	 * setup the defualt cateogires and load them into the map
	 * @brief Unsplash class constructor
	 * @author David Tkachuk
	 */
		Unsplash();
		~Unsplash();

		/**
		 * Fetch a random background from unsplash
		 * @return The background object, or null if there was an error
		 * @brief Fetch a random background from unsplash
		 * @author David Tkachuk
		 */
		UnsplashBackground* getRandomBackground();

		/**
		 * Download a background image from unsplash
		 * @param background The background to donwload
		 * @param width The width to download the image at
		 * @param height The height to download the image at
		 * @return True if success, false otherwise
		 * @brief Download some background
		 * @author David Tkachuk
		 */
		bool downloadBackground(UnsplashBackground* background, int width = 0, int height = 0);


		/**
		 * Get the current background image file name
		 * @return Can be the main or buffer background image
		 * @brief Get the  background image file name
		 * @author David Tkachuk
		 */
		std::string getBackgroundImage();

		/**
		 * Get all categories
		 * @return A map of category id to category name
		 * @brief Get all categories
		 * @details This is a map of category id to category name
		 * @authors David Tkachuk
		 */
		std::map<std::string, std::string> getCategories();


		/**
		 * Get current category ID
		 * @return The cateogiry id
		 * @brief Get current category ID
		 */
		std::string getCurrentCategoryId();


		/**
		 * Get the category name of current category
		 * @return The current category name
		 * @brief Current category name
		 * @author David Tkachuk
		 */
		std::string getCurrentCategoryName();

		/**
		 * Get the category name of a category id
		 * @param id The category id
		 * @return The category name
		 * @brief Get the category name of a category id
		 */
		std::string getCategoryName(std::string id);

	private:

		/**
		 * Hard coded "loading" of al lcategories and thier names
		 * @brief loads the background categories
		 * @see https://unsplash.com/documentation#list-all-topics
		 * @author David Tkachuk
		 */
		void loadCategories();
};


#endif //HOMEHIVE_UNSPLASH_H
