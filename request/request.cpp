/**
 * HTTP Request Class Implementation
 *
 * CS3307 Individual Assignment
 * David Tkachuk <dtkachu2@uwo.ca>
 * February 7th 2023
 */

#include "request.h"

static size_t writeStringCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}

size_t writeBinaryCallback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
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
	this->filePointer = nullptr;
	this->isBinaryDownload = false;
}

/**
 * Class destructor to clean things up
 */
Request::~Request() {
	this->url.clear();
	this->dataBuffer.clear();
	this->errorBuffer.clear();
	this->isBinaryDownload = false;
}

/**
 * Execute the request
 * @return True if request successful, false otherwise
 */
bool Request::execute() {
	if (this->curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// handle binary downloads
		if (this->isBinaryDownload && this->filePointer) {
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBinaryCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, this->filePointer);
		} else { // handles stringy responses
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeStringCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(this->dataBuffer));
		}

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

/**
 * Write the response to a file
 * @param path The file's path
 * @return
 */
bool Request::writeToFile(std::string path) {
	FILE* fp;
	fp = fopen(path.c_str(), "wb");

	// return false if the file ponter failed?
	return (fp != nullptr &&  this->writeToFile(fp));
}

/**
 * Write the response to an existing file pointer
 * @param file The file pointer
 * @return
 */
bool Request::writeToFile(FILE* file) {
	this->isBinaryDownload = true;
	this->filePointer = file;
	return file != nullptr;
}

/**
 * Returns the file pointer to the file we're writing to, if applicable
 * @return The file pointer, null if not set or not a binary download
 */
FILE *Request::getOutputFile() {
	return this->filePointer;
}

