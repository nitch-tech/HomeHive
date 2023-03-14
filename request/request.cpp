#include "request.h"
#include <iostream>

using std::string;



Request::Request(string url) {
    this->url = url;

    curl = curl_easy_init();

    chunk.memory = (char*)malloc(1);
    chunk.size = 0;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemory);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
}

Request::~Request() {
    curl_easy_cleanup(curl);
    free(chunk.memory);
}

size_t Request::writeMemory(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void Request::execute() {
    response = curl_easy_perform(curl);
}

char* Request::result() {
    if (response != CURLE_OK) {
        std::cerr << "Request Failed!%s\n", curl_easy_strerror(response);
        return NULL;

    } else {
        printres();
        //std::cout << "Anorther test" << std::endl;
        return chunk.memory;
    }
}
void Request::printres() {




}
