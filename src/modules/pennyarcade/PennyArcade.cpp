#include "PennyArcade.h"

#include <iostream>
#include <curl/curl.h>
#include <gloox/message.h>
#include <tidy.h>
#include <buffio.h>
#include <pugixml.hpp>

#include "../../Channel.h"

// Initialize the module (which automatically adds it to the std::map in Module.h
PennyArcade pa("PennyArcade");

CURL* curl;
std::string data; // will hold the website's content

std::size_t writeCallback(char* buf, std::size_t size, std::size_t nmemb, void* up)
{
    // LibCurl callbacks require this signature
    // buf is a pointer to data from libcurl
    // size * nmemb is the size of the buffer
    for (unsigned int c = 0; c < size * nmemb; c++) {
        data.push_back(buf[c]);
    }

    return size * nmemb; // Tell curl how many bytes we handled
}

PennyArcade::PennyArcade(const std::string& name) : Module(name)
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
}

PennyArcade::~PennyArcade()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void PennyArcade::accept(Channel* src, const gloox::Message& msg)
{
    const std::string text = msg.body();

    if (text.compare("!pa") == 0) {
        // TODO: Wrap this process so it doesn't need to be repeated for every plugin.
        curl_easy_setopt(curl, CURLOPT_URL, "http://penny-arcade.com/comic");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        //curl_easy_setopt ( curl, CURLOPT_VERBOSE, 1L ); // Tell curl to output it's progress

        // Actually grab the website
        curl_easy_perform(curl);

        // Turn the HTML into XHTML (valid xml)
        TidyDoc tdoc = tidyCreate();
        bool ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
        int rc = -1;
        TidyBuffer output = {0};
        TidyBuffer errbuf = {0};

        if (ok) {
            rc = tidySetErrorBuffer(tdoc, &errbuf);       // capture diagnostics
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

        if (rc > 1) {
            rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
        }

        if (rc >= 0) {
            rc = tidySaveBuffer(tdoc, &output);       // pretty print
        }

        pugi::xml_document doc;
        auto result = doc.load_buffer(output.bp, output.size);

        if (result) {
            // Success
            pugi::xpath_node paImage = doc.select_single_node("//*[@id='comicFrame']/a/img");
            src->speak(paImage.node().attribute("src").value());
        } else {
            // Log the failure
        }
    } else {
        // nothing.
    }
}
