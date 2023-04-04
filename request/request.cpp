/**
 * HTTP Request Class Implementation
 *
 * CS3307 Individual Assignment
 * David Tkachuk <dtkachu2@uwo.ca>
 * February 7th 2023
 */

#include "request.h"

/**
 * Curl write string callback
 * @brief Curl write string callback
 * @param contents the data to write
 * @param size the size of the data
 * @param nmemb size of data
 * @param userp data to write to?
 * @return The size of the data
 */
static size_t writeStringCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}

/**
 * Curl write binary callback
 * @param ptr the data pointer to write
 * @param size  the size of the data
 * @param nmemb number of mem
 * @param stream the file stream
 * @return size of written data?
 * @brief Curl write binary callback
 */
size_t writeBinaryCallback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}


/**
 * Class constructor to setup request
 * @param url The HTTP URL to send a request to
 * @brief Class constructor to setup request
 * @author David Tkachuk
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
 * @brief Class destructor to clean things up
 * @author David Tkachuk
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
 * @brief Execute the request
 * @author David Tkachuk
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
 * @brief Returns the raw response body from the HTTP request
 * @author David Tkachuk
 */
std::string Request::getResponse() {
	return this->dataBuffer;
}

/**
 * Get the curl error details if applicable as string
 * @return The request error details
 * @brief Get the curl error detials
 * @author David Tkachuk
 */
std::string Request::getError() {
	return this->errorBuffer;
}

/**
 * Get the curl error code if applicable
 * @return The request error code
 * @brief Get the curl error code
 * @author David Tkachuk
 */
CURLcode Request::getErrorCode() {
	return this->res;
}

/**
 * Write the response to a file
 * @param path The file's path
 * @return True if the file was written successfully, false otherwise
 * @brief Write the response to a file
 * @author David Tkachuk
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
 * @return True if the file was written successfully, false otherwise
 * @brief Write the response to an existing file pointer
 * @author David Tkachuk
 */
bool Request::writeToFile(FILE* file) {
	this->isBinaryDownload = true;
	this->filePointer = file;
	return file != nullptr;
}

/**
 * Returns the file pointer to the file we're writing to, if applicable
 * @return The file pointer, null if not set or not a binary download
 * @brief Returns the file pointer to the file we're writing to, if applicable
 * @author David Tkachuk
 */
FILE *Request::getOutputFile() {
	return this->filePointer;
}

