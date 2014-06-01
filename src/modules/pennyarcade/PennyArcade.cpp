#include "PennyArcade.h"

#include <iostream>
#include <gloox/message.h>
#include <pugixml.hpp>

#include "../../Channel.h"

// Initialize the module (which automatically adds it to the std::map in Module.h
PennyArcade pa("PennyArcade");

const std::string PA_URL = "http://penny-arcade.com/comic";

PennyArcade::PennyArcade(const std::string& name)
    : CommandModule(name, {"pa", "pennyarcade"}, '!')
{
}

PennyArcade::~PennyArcade()
{
}

void PennyArcade::commandAction(Channel* src, const std::vector<std::string>& args)
{
    int response = 0; // 0 means no response
    switch (args.size()) {
        case 1:
            if (args[0] == "random") response = 2; // 2 means get a random comic
            else if (args[0] == "latest") response = 1; // 1 means just get latest comic
            break;
        case 0:
            response = 1; // the default
            break;
        default:
            response = 0;
    }

    if (response != 0) {
        pugi::xml_document* doc = Module::scraper.loadUrl(PA_URL);
        if (doc == nullptr) {
            // TODO: Implement proper logging here.
            std::cout << "Error retrieving URL: " << PA_URL << std::endl;
        }

        // This method just follows random link that gets generated at load time
        // on the latest comic page.
        // Unfortunately, this means that it takes twice as long to get a random
        // comic. It can't be easily done another way, I don't think.
        if (response == 2) {
            std::string random_url = doc->select_single_node("//*[@id='comic']/div[2]/ul[1]/li[3]/a").node().attribute("href").value();
            delete doc;
            doc = Module::scraper.loadUrl(random_url);
        }
        pugi::xpath_node paImage = doc->select_single_node("//*[@id='comicFrame']/a/img");
        std::string title = paImage.node().attribute("alt").value();
        std::string imgLink = paImage.node().attribute("src").value();
        src->speak(title + ": " + imgLink);
    }
}
