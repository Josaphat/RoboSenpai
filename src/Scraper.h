#pragma once

#include <curl/curl.h>
#include <string>

namespace pugi {
    class xml_document;
}

class Scraper {
public:
    Scraper();
    virtual ~Scraper();

    pugi::xml_document* loadUrl(const std::string& url);
    friend std::size_t writeCallback(char*,std::size_t, std::size_t, void*);
private:
    CURL* curl;
    std::string data;
};
