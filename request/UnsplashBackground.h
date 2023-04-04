//
// Created by dave on 13/03/23.
//

#ifndef HOMEHIVE_UNSPLASHBACKGROUND_H
#define HOMEHIVE_UNSPLASHBACKGROUND_H


#include <string>

/**
 * Unsplash background class
 *
 * This class represents a background image from unsplash
 * and contains all the information about the image
 *
 * @author David Tkachuk
 * @brief Unsplash background class
 */
class UnsplashBackground {
	private:
		std::string id;
		int width;
		int height;
		std::string description;
		std::string url;

	public:
		/**
		 * Create a new unsplash background object
		 * @param id the background's unique ID
		 * @brief Create a new unsplash background object
		 * @author David Tkachuk
		 */
		explicit UnsplashBackground(std::string id);
		~UnsplashBackground();

		/**
		 * Set the width of the background
		 * @param width The width of the background
		 * @brief Set the width of the background
		 * @author David Tkachuk
		 */
		void setWidth(int width);

		/**
		 * Set the height of the background
		 * @param height The height of the background
		 * @brief Set the height of the background
		 * @author David Tkachuk
		 */
		void setHeight(int height);

		/**
		 * Set the description of the background
		 * @param desc The description of the background
		 * @brief Set the description of the background
		 * @author David Tkachuk
		 */
		void setDescription(std::string desc);

		/**
		 * Set the URL of the background
		 * @param url The URL of the background
		 * @brief Set the URL of the background
		 * @author David Tkachuk
		 */
		void setURL(std::string url);

		/**
		 * Get the width of the background
		 * @return The width of the background
		 * @brief Get the width of the background
		 * @author David Tkachuk
		 */
		int getWidth();

		/**
		 * Get the height of the background
		 * @return The height of the background
		 * @brief Get the height of the background
		 * @author David Tkachuk
		 */
		int getHeight();


		/**
		 * Get the ID of the background
		 * @return The ID of the background
		 * @brief Get the ID of the background
		 * @author David Tkachuk
		 */
		std::string getId();

		/**
		 * Get the description of the background
		 * 	* @return The description of the background
		 * 	* @brief Get the description of the background
		 * 	* @author David Tkachuk
		 */
		std::string getDescription();

		/**
		 * Get the URL of the background
		 * @return The URL of the background
		 * @brief Get the URL of the background
		 * 	* @brief Get the URL of the background
		 */
		std::string getURL();
};


#endif //HOMEHIVE_UNSPLASHBACKGROUND_H
