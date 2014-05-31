#pragma once

#include <gloox/mucroomhandler.h>
#include <gloox/presence.h>

#include "BotCore.h"

namespace gloox {
    class Client;
}
class Connection;

//
/// The Channel object provides the interface to a multi-user chat. It does
/// this by wrapping a gloox MUCRoom. When a message is received it gets passed
/// to the bot for processing.
//
class Channel : public gloox::MUCRoomHandler {
public:
    Channel(BotCore* bot, Connection* connection, gloox::Client* client, const gloox::JID& roomJID);
    virtual ~Channel();

public: // Inherited
    virtual void handleMUCParticipantPresence(gloox::MUCRoom* room, const gloox::MUCRoomParticipant participant, const gloox::Presence& presence);
    virtual void handleMUCMessage(gloox::MUCRoom* room, const gloox::Message& msg, bool priv);
    virtual bool handleMUCRoomCreation(gloox::MUCRoom* room);
    virtual void handleMUCSubject(gloox::MUCRoom* room, const std::string& nick, const std::string& subject);
    virtual void handleMUCInviteDecline(gloox::MUCRoom* room, const gloox::JID& invitee, const std::string& reason);
    virtual void handleMUCError(gloox::MUCRoom* room, gloox::StanzaError error);
    virtual void handleMUCInfo(gloox::MUCRoom* room, int features, const std::string& name, const gloox::DataForm* infoForm);
    virtual void handleMUCItems(gloox::MUCRoom* room, const gloox::Disco::ItemList& items);

public:
    //
    /// Broadcasts a message in this Channel's MUCRoom.
    //
    void speak(const std::string& message);

    //
    /// Joins the Channel.
    /// Before this method is called, none of the event handlers will be activated.
    //
    void join(gloox::Presence::PresenceType type = gloox::Presence::Available, const std::string& status = gloox::EmptyString, int priority = 0);

private:
    BotCore* bot;
    Connection* connection;
    gloox::MUCRoom* room;
};
