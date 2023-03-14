#ifndef REQUEST_H
#define REQUEST_H

#include "curl/curl.h"
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include "json.hpp"



using namespace std;
using std::string;
using json = nlohmann::json;

struct MemoryStruct {
    char *memory;
    size_t size;
};

class Request {
public:
    string url;
    CURL *curl;
    CURLcode response;
    struct MemoryStruct chunk;
    static size_t writeMemory(void *contents, size_t size, size_t nmemb, void *userp);
public:
    Request(string url);
    ~Request();
    void execute();
    char* result();
    void printres();
};

#endif
