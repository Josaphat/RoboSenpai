#include "Scraper.h"

#include <pugixml.hpp>
#include <tidy.h>
#include <buffio.h>

// libcurl callback
std::size_t writeCallback(char*, std::size_t, std::size_t, void*);

Scraper::Scraper() : curl(), data("")
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
}

Scraper::~Scraper()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

pugi::xml_document* Scraper::loadUrl(const std::string& url)
{
    // Make sure we don't have any data from the last time we ran curl
    data.clear();

    // Set up curl
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    // Some services don't reply if you don't give them a User Agent.
    // Give what the curl commandline util gives
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.37.0-RoboSenpai");
//    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Logging

    // Tell curl to do its thing and grab the stuff at the url we gave it
    curl_easy_perform(curl);

    // The data is now stored in this->data
    // Turn it into valid XML
    TidyDoc tdoc = tidyCreate();
    TidyBuffer output;
    TidyBuffer errbuf;
    int rc = -1;
    bool ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
    if (ok){
        // capture diagnostics
        rc = tidySetErrorBuffer(tdoc, &errbuf);
    }
    if (rc >= 0) {
        rc = tidyParseString(tdoc, data.c_str());
    }
    if (rc >= 0) {
        rc = tidyCleanAndRepair(tdoc);
    }
    if (rc >= 0) {
        rc = tidyRunDiagnostics(tdoc);
    }
    if(rc >1) {
        rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
    }
    if(rc >=0) {
        rc = tidySaveBuffer(tdoc, &output);
    }
    pugi::xml_document* doc = new pugi::xml_document;
    auto result = doc->load_buffer(output.bp, output.size);
    if (result) {
        // Success!
    } else {
        doc = nullptr;
    }
    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
    return doc;
}

pugi::xml_document* Scraper::loadFeedUrl(const std::string& url)
{
    data.clear();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    // Some services don't reply if you don't give them a User Agent.
    // Give what the curl commandline utility gives
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.37.0-RoboSenpai");
//    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_perform(curl);
    pugi::xml_document* doc = new pugi::xml_document;
    auto result = doc->load(data.c_str());
    if(result) {
        // Success!
    }
    else {
        doc = nullptr;
    }
    return doc;
}

std::size_t writeCallback(char* buf, std::size_t size, std::size_t nmemb, void* Scraper_ref)
{
    Scraper* scraper = static_cast<Scraper*>(Scraper_ref);
    for (unsigned int i = 0; i < size * nmemb; i++) {
        scraper->data.push_back(buf[i]);
    }
    return size * nmemb; // tell curl how many bytes we handled
}
