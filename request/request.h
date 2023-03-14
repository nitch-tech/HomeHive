/**
 * HTTP Request Definition
 *
 * CS3307 Individual Assignment
 * David Tkachuk <dtkachu2@uwo.ca>
 * February 7th 2023
 */

#ifndef CS3307_REQUEST_H
#define CS3307_REQUEST_H


#include <string>
#include <curl/curl.h>

/**
 * Request Class
 *
 * Allows us to send some HTTP request and easily extract the error or response.
 */
class Request {
	private:
		std::string url;
		std::string dataBuffer;
		std::string errorBuffer;
		CURL* curl;
		CURLcode res;

	public:
		/**
		 * Class constructor to setup request
		 * @param url The HTTP URL to send a request to
		 */
		explicit Request(std::string url);

		/**
		 * Class destructor to clean things up
		 */
		~Request();

		/**
		 * Execute the request
		 * @return True if request successful, false otherwise
		 */
		bool execute();

		/**
		 * Returns the raw response body from the HTTP request
		 * @return String response data
		 */
		std::string getResponse();

		/**
		 * @return The request error code
		 */
		CURLcode getErrorCode();

		/**
		 * @return The request error details
		 */
		std::string getError();
};


#endif
