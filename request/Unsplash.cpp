//
// Created by dave on 13/03/23.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include "Unsplash.h"

const std::string API_KEY = "Eimmb-Q4YT2OgHDNhqgdynudnrDiWx4_heqO0IHQoaw";
const std::string DEFAULT_TOPIC = "Fzo3zuOHN6w";

Unsplash::Unsplash() {
}

Unsplash::~Unsplash() {
}

UnsplashBackground *Unsplash::getRandomBackground() {
	Request* req = new Request("https://api.unsplash.com/photos/random?topics=" + DEFAULT_TOPIC + "&client_id=" + API_KEY);
	if (!req->execute()) {
		std::cout << "Error: " << req->getError() << std::endl;
		return nullptr;
	}

	auto res = nlohmann::json::parse(req->getResponse());
	std::cout << res.dump() << std::endl;

	auto bg = new UnsplashBackground(res["id"]);
	bg->setWidth(res["width"]);
	bg->setHeight(res["height"]);
	bg->setDescription(res["description"]);
	bg->setURL(res["urls"]["full"]);
	return bg;
}
