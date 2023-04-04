//
// Created by dave on 13/03/23.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include "Unsplash.h"

const std::string API_KEY = "Eimmb-Q4YT2OgHDNhqgdynudnrDiWx4_heqO0IHQoaw";
//const std::string API_KEY = "LWJuhe2HqclZbAa0JbprJcTzyVE1lycSqIL1MTebZHM";
const std::string BG_IMG_MAIN = "background.jpg";
const std::string BG_IMG_BUFF = "background2.jpg";

/**
 * Unsplash class constructor
 * setup the defualt cateogires and load them into the map
 * @brief Unsplash class constructor
 * @author David Tkachuk
 */
Unsplash::Unsplash() {
	this->isBufferImage = false;
	this->categories = std::map<std::string, std::string>();
	this->loadCategories();
	this->currentCategoryId = "Fzo3zuOHN6w";
}

Unsplash::~Unsplash() {
	if (this->file) fclose(this->file);
}

/**
 * Fetch a random background from unsplash
 * @return The background object, or null if there was an error
 * @brief Fetch a random background from unsplash
 * @author David Tkachuk
 */
UnsplashBackground *Unsplash::getRandomBackground() {
	Request* req = new Request(
					"https://api.unsplash.com/photos/random?topics=" +
					this->currentCategoryId +
					"&client_id=" + API_KEY +
					"&orientation=landscape");
	if (!req->execute()) {
		std::cout << "Error: " << req->getError() << std::endl;
		return nullptr;
	}

	auto res = nlohmann::json::parse(req->getResponse());

	auto bg = new UnsplashBackground(res["id"]);
	bg->setWidth(res["width"]);
	bg->setHeight(res["height"]);

	// @TODO check if alt_description is null and see if we need this? maybe a little caption label?
//	bg->setDescription(res["alt_description"]);
	bg->setURL(res["urls"]["full"]);

	delete req;
	return bg;
}

/**
 * Download a background image from unsplash
 * @param background The background to donwload
 * @param width The width to download the image at
 * @param height The height to download the image at
 * @return True if success, false otherwise
 * @brief Download some background
 * @author David Tkachuk
 */
bool Unsplash::downloadBackground(
				UnsplashBackground *background,
				int width,
				int height
) {
	std::string url = background->getURL() + "&fit=max&crop=entropy";

	// specify width and heights, and let unsplash crop it for us <3
	if (width > 0) {
		url += "&w=" + std::to_string(width);
	}
	if (height > 0) {
		url += "&h=" + std::to_string(height);
	}

	this->isBufferImage = !this->isBufferImage;

	Request* req = new Request(url);
	FILE* fp = fopen(this->getBackgroundImage().c_str(), "wb");
	if (!req->writeToFile(fp)) {
		std::cout << "Error: todo" << std::endl;
		fclose(fp);
		delete req;
		return false;
	}
	if (!req->execute()) {
		fclose(fp);
		std::cout << "Error: " << req->getError() << std::endl;
		delete req;
		fclose(fp);
		return false;
	}
	fclose(fp);
	delete req;

	// return req->getOutputFile();
	return true;
}

/**
 * Get the current background image file name
 * @return Can be the main or buffer background image
 * @brief Get the  background image file name
 * @author David Tkachuk
 */
std::string Unsplash::getBackgroundImage() {
	return this->isBufferImage ? BG_IMG_BUFF : BG_IMG_MAIN;
}

/**
 * Get current category ID
 * @return The cateogiry id
 * @brief Get current category ID
 */
std::string Unsplash::getCurrentCategoryId() {
	return this->currentCategoryId;
}

/**
 * Get the category name of current category
 * @return The current category name
 * @brief Current category name
 * @author David Tkachuk
 */
std::string Unsplash::getCurrentCategoryName() {
	return this->getCategoryName(this->currentCategoryId);
}

/**
 * Get the category name of a category id
 * @param id The category id
 * @return The category name
 * @brief Get the category name of a category id
 */
std::string Unsplash::getCategoryName(std::string id) {
	return this->categories[id];
}

/**
 * Get all categories
 * @return A map of category id to category name
 * @brief Get all categories
 * @details This is a map of category id to category name
 * @authors David Tkachuk
 */
std::map<std::string, std::string> Unsplash::getCategories() {
	return this->categories;
}

/**
 * Hard coded "loading" of al lcategories and thier names
 * @brief loads the background categories
 * @see https://unsplash.com/documentation#list-all-topics
 * @author David Tkachuk
 */
void Unsplash::loadCategories() {
	this->categories["Fzo3zuOHN6w"] = "Travel";
	this->categories["6sMVjTLSkeQ"] = "Nature";
	this->categories["xHxYTMHLgOc"] = "Street Photography";
	this->categories["iUIsnVtjB0Y"] = "Textures & Patterns";
	this->categories["Jpg6Kidl-Hk"] = "Animals";
	this->categories["M8jVbLbTRws"] = "Architecture";
	this->categories["bDo48cUhwnY"] = "Arts & Culture";
	this->categories["_8zFHuhRhyo"] = "Spiritual";
	this->categories["bo8jQKTaE0Y"] = "Random";
}
