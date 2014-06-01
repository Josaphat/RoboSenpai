#pragma once

#include <curl/curl.h>
#include <string>

namespace pugi {
    class xml_document;
}

/// A wrapper for curl and HTML Tidy. They're pretty unwieldy and it's generally
/// common functionality for most of these modules: scraping data from the web.
class Scraper {
public:
    Scraper();
    virtual ~Scraper();

    /// Returns a nullptr if the data at the given url could not be converted.
    pugi::xml_document* loadUrl(const std::string& url);
    pugi::xml_document* loadFeedUrl(const std::string& url);
    friend std::size_t writeCallback(char*, std::size_t, std::size_t, void*);
private:
    CURL* curl;
    std::string data;
};
