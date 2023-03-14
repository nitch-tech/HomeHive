/**
 * HTTP Request Class Implementation
 *
 * CS3307 Individual Assignment
 * David Tkachuk <dtkachu2@uwo.ca>
 * February 7th 2023
 */

#include "request.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}

/**
 * Class constructor to setup request
 * @param url The HTTP URL to send a request to
 */
Request::Request(std::string url) {
	this->url = url;
	this->curl = curl_easy_init();
	this->errorBuffer = "";
	this->dataBuffer = "";
}

/**
 * Class destructor to clean things up
 */
Request::~Request() {
	this->url.clear();
	this->dataBuffer.clear();
	this->errorBuffer.clear();
}

/**
 * Execute the request
 * @return True if request successful, false otherwise
 */
bool Request::execute() {
	if (this->curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(this->dataBuffer));
		// curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &(this->errorBuffer));
		this->res = curl_easy_perform(curl);
		if (this->res != CURLE_OK) {
			this->errorBuffer = curl_easy_strerror(this->res);
		}
		curl_easy_cleanup(curl);

		// return true if the response was successful
		return this->res == CURLE_OK;
	}

	return false;
}

/**
 * Returns the raw response body from the HTTP request
 * @return String response data
 */
std::string Request::getResponse() {
	return this->dataBuffer;
}

/**
 * @return The request error details
 */
std::string Request::getError() {
	return this->errorBuffer;
}

/**
 * @return The request error code
 */
CURLcode Request::getErrorCode() {
	return this->res;
}
