#pragma once

#include <map>
#include <string>
#include "Scraper.h"

// Forward declarations
namespace gloox {
    class Message;
}
class BotCore;
class Channel;

//
/// Defines the interface of a basic module.
/// Each module has a string name with which it is refered to in the config
/// file. It is expected that modules use the Attach By Initialization Idiom
/// to add themselves into the map.
//
class Module {
public:
    Module(const std::string& name);
    virtual ~Module();

    //
    /// This method is the entry point for modules.
    /// They receive the channel on which a message was received and a
    /// reference to the gloox::Message object.
    //
    virtual void accept(Channel* src, const gloox::Message& msg) = 0;

    //
    /// This is the global registry for Modules. It creates a mapping between
    /// strings and the modules themselves so that they can be referenced in the
    /// config file and used accordingly.
    ///
    /// Note that *all* modules (which properly attach themselves) will be
    /// instantiated and a reference placed in this map, even if they are
    /// disabled in the configuration.
    //
    static std::map<std::string, Module*> moduleMap;

protected:
    /// A convenience object which provides the functionality to request a URL
    /// and get back XHTML for subclasses.
    static Scraper scraper;
    BotCore* bot;
};
