#pragma once

#include <queue>
#include <vector>

#include <gloox/mucroomhandler.h>
#include <gloox/presence.h>

#include "BotCore.h"

namespace gloox {
    class Client;
}
class Connection;

class Channel : public gloox::MUCRoomHandler {
public:
    Channel(BotCore* bot, Connection* connection, gloox::Client* client, const gloox::JID& roomJID);
    virtual ~Channel();
    void setRoom(gloox::MUCRoom* room);

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
    void speak(const std::string& message);
    void join(gloox::Presence::PresenceType type = gloox::Presence::Available, const std::string& status = gloox::EmptyString, int priority = 0);

private:
    BotCore* bot;
    Connection* connection;
    gloox::MUCRoom* room;
    std::queue<std::string> lastSpoken;
};
