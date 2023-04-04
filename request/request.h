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
 * @brief Request Class
 * @author David Tkachuk
 */
class Request {
	private:
		std::string url;
		std::string dataBuffer;
		std::string errorBuffer;
		CURL* curl;
		CURLcode res;

		/**
		 * Filer pointer to wwrite to, if its a binary download
		 */
		FILE* filePointer;

		/**
		 * Whether te reqeust is a binary
		 *
		 * If true, we're dealing with binary data and will write data to a file pointer.
		 */
		bool isBinaryDownload;

	public:
		/**
		 * Class constructor to setup request
		 * @param url The HTTP URL to send a request to
		 * @brief Class constructor to setup request
		 * @author David Tkachuk
		 */
		explicit Request(std::string url);

		/**
		 * Class destructor to clean things up
		 * @brief Class destructor to clean things up
		 * @author David Tkachuk
		 */
		~Request();

		/**
		 * Execute the request
		 * @return True if request successful, false otherwise
		 * @brief Execute the request
		 * @author David Tkachuk
		 */
		bool execute();

		/**
		 * Write the response to a file
		 * @param path The file's path
		 * @return True if the file was written successfully, false otherwise
		 * @brief Write the response to a file
		 * @author David Tkachuk
		 */
		bool writeToFile(std::string path);

		/**
		 * Write the response to an existing file pointer
		 * @param file The file pointer
		 * @return
		 */
		bool writeToFile(FILE* file);

		/**
		 * Write the response to an existing file pointer
		 * @param file The file pointer
		 * @return True if the file was written successfully, false otherwise
		 * @brief Write the response to an existing file pointer
		 * @author David Tkachuk
		 */
		FILE* getOutputFile();

		/**
		 * Returns the raw response body from the HTTP request
		 * @return String response data
		 * @brief Returns the raw response body from the HTTP request
		 * @author David Tkachuk
		 */
		std::string getResponse();

		/**
		 * Get the curl error code if applicable
		 * @return The request error code
		 * @brief Get the curl error code
		 * @author David Tkachuk
		 */
		CURLcode getErrorCode();

		/**
		 * Get the curl error details if applicable as string
		 * @return The request error details
		 * @brief Get the curl error detials
		 * @author David Tkachuk
		 */
		std::string getError();
};


#endif
