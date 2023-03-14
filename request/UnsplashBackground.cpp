//
// Created by dave on 13/03/23.
//

#include "UnsplashBackground.h"

UnsplashBackground::UnsplashBackground(std::string id) {
	this->id = id;
	this->width = 0;
	this->height = 0;
	this->description = "Unknown image";
}

UnsplashBackground::~UnsplashBackground() {
}

void UnsplashBackground::setWidth(int width) {
	this->width = width;
}

void UnsplashBackground::setHeight(int height) {
	this->height = height;
}

void UnsplashBackground::setDescription(std::string desc) {
	this->description = desc;
}

void UnsplashBackground::setURL(std::string url) {
	this->url = url;
}

int UnsplashBackground::getWidth() {
	return this->width;
}

int UnsplashBackground::getHeight() {
	return this->height;
}

std::string UnsplashBackground::getId() {
	return this->id;
}

std::string UnsplashBackground::getDescription() {
	return this->description;
}

std::string UnsplashBackground::getURL() {
	return this->url;
}
