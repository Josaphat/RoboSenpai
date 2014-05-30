#include "PennyArcade.h"

#include <iostream>
#include <gloox/message.h>
#include <pugixml.hpp>

#include "../../Channel.h"

// Initialize the module (which automatically adds it to the std::map in Module.h
PennyArcade pa("PennyArcade");

const std::string PA_URL = "http://penny-arcade.com/comic";

PennyArcade::PennyArcade(const std::string& name) : Module(name)
{
}

PennyArcade::~PennyArcade()
{
}

void PennyArcade::accept(Channel* src, const gloox::Message& msg)
{
    const std::string text = msg.body();

    if (text == "!pa" || text == "!pa latest" || text == "!pa random") {
        pugi::xml_document * doc = scraper.loadUrl(PA_URL);
        if (doc == nullptr) {
            // TODO: Implement proper logging here.
            std::cout << "Error retrieving URL: " << PA_URL << std::endl;
        }

        // This method just follows random link that gets generated at load time
        // on the latest comic page.
        // Unfortunately, this means that it takes twice as long to get a random
        // comic.
        if(text == "!pa random") {
            std::string random_url = doc->select_single_node("//*[@id='comic']/div[2]/ul[1]/li[3]/a").node().attribute("href").value();
            delete doc;
            doc = scraper.loadUrl(random_url);
        }
        pugi::xpath_node paImage = doc->select_single_node("//*[@id='comicFrame']/a/img");
        std::string title = paImage.node().attribute("alt").value();
        std::string imgLink = paImage.node().attribute("src").value();
        src->speak(title + ": " + imgLink);
    } else {
        // This isn't the command we're looking for.
    }
}
