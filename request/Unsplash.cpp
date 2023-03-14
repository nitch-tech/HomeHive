//
// Created by dave on 13/03/23.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include "Unsplash.h"

const std::string API_KEY = "LWJuhe2HqclZbAa0JbprJcTzyVE1lycSqIL1MTebZHM"; // "Eimmb-Q4YT2OgHDNhqgdynudnrDiWx4_heqO0IHQoaw";
const std::string DEFAULT_TOPIC = "Fzo3zuOHN6w";

const std::string BG_IMG_MAIN = "background.jpg";
const std::string BG_IMG_BUFF = "background2.jpg";

Unsplash::Unsplash() {
	this->isBufferImage = false;
}

Unsplash::~Unsplash() {
	if (this->file) fclose(this->file);
}

UnsplashBackground *Unsplash::getRandomBackground() {
	Request* req = new Request("https://api.unsplash.com/photos/random?topics=" + DEFAULT_TOPIC + "&client_id=" + API_KEY + "&orientation=landscape");
	if (!req->execute()) {
		std::cout << "Error: " << req->getError() << std::endl;
		return nullptr;
	}

	auto res = nlohmann::json::parse(req->getResponse());
	std::cout << res.dump() << std::endl;

	auto bg = new UnsplashBackground(res["id"]);
	bg->setWidth(res["width"]);
	bg->setHeight(res["height"]);
//	bg->setDescription(res["alt_description"]);
	bg->setURL(res["urls"]["full"]);

	delete req;
	return bg;
}

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

std::string Unsplash::getBackgroundImage() {
	return this->isBufferImage ? BG_IMG_BUFF : BG_IMG_MAIN;
}
