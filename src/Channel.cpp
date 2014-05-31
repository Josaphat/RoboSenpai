#include "Channel.h"

#include <iostream>

#include <gloox/client.h>
#include <gloox/mucroom.h>
#include <gloox/presence.h>
#include <gloox/message.h>
#include <gloox/jid.h>
#include <gloox/disco.h>
#include <gloox/presence.h>

#include "BotCore.h"
#include "Connection.h"

Channel::Channel(BotCore* bot, Connection* connection, gloox::Client* client, const gloox::JID& roomJID)
    : bot(bot), connection(connection), room(new gloox::MUCRoom(client, roomJID, this, 0))
{
}

Channel::~Channel()
{
}

void Channel::handleMUCParticipantPresence(gloox::MUCRoom* room, const gloox::MUCRoomParticipant participant, const gloox::Presence& presence)
{
    using std::cout;
    using gloox::Presence;

    // TODO: This should query the plugins to see if they care to handle the event
    cout << "[" << room->name() << "] " << participant.nick->resource() << " ";
    Presence::PresenceType p = presence.subtype();

    switch (p) {
        case Presence::Available:
            cout << "is online.";
            break;

        case Presence::Chat:
            cout << "is 'available for chat.'";
            break;

        case Presence::Away:
            cout << "went away.";
            break;

        case Presence::DND:
            cout << "went DND.";
            break;

        case Presence::XA:
            cout << "went XA.";
            break;

        case Presence::Unavailable:
            cout << "went offline.";
            break;

        case Presence::Probe:
            cout << "== Presence probe ==";
            break;

        case Presence::Error:
            cout << "== Presence error ==";
            break;

        case Presence::Invalid:
            cout << "== The stanza is invalid ==";
            break;

        default:
            cout << "== default presence handling ==";
            break;
    }

    cout << std::endl;
}

void Channel::handleMUCMessage(gloox::MUCRoom* room, const gloox::Message& msg, bool priv)
{
    if (msg.from().resource() == bot->nick) {
        // The bot got a message from itself.
    }
    else {
        // TODO: Log this.
        std::cout << "[" << room->name() << ": " << msg.from().resource() << "(" << priv << ") ]  " << msg.body() << std::endl;
        bot->processMessage(this, msg, priv);
    }
}

bool Channel::handleMUCRoomCreation(gloox::MUCRoom* /*room*/)
{
    // TODO: This is a stub. What does scenario does this handle and would plugins care?
    return true;
}

void Channel::handleMUCSubject(gloox::MUCRoom* room, const std::string& nick, const std::string& subject)
{
    std::cout << room->name() << " Subject is \"" << subject << "\"";
    if (nick.empty()) {
        // If no nick is given, then the topic was already set (i.e. we just joined the room).
        std::cout << std::endl;
    }
    else {
        std::cout << " set by " << nick << std::endl;
    }
}

void Channel::handleMUCInviteDecline(gloox::MUCRoom* /*room*/, const gloox::JID& /*invitee*/, const std::string& /*reason*/)
{
    // TODO: This is a stub. Log that this method was called but nothing was done.
}

void Channel::handleMUCError(gloox::MUCRoom* room, gloox::StanzaError error)
{
    using gloox::StanzaError;
    using std::cout;
    // TODO: Log this. Perhaps attempt a reconnect/rejoin.
    cout << "[" << room->name() << "] Channel Error: ";
    switch (error) {
        case StanzaError::StanzaErrorBadRequest:
            cout << "Bad Request.";
            break;

        case StanzaError::StanzaErrorConflict:
            cout << "Conflict.";
            break;

        case StanzaError::StanzaErrorFeatureNotImplemented:
            cout << "Feature not implemented.";
            break;

        case StanzaError::StanzaErrorForbidden:
            cout << "Forbidden. ";
            break;

        case StanzaError::StanzaErrorGone:
            cout << "Gone.";
            break;

        case StanzaError::StanzaErrorInternalServerError:
            cout << "Internal server error.";
            break;

        case StanzaError::StanzaErrorItemNotFound:
            cout << "Item not found.";
            break;

        case StanzaError::StanzaErrorJidMalformed:
            cout << "JID Malformed.";
            break;

        case StanzaError::StanzaErrorNotAcceptable:
            cout << "Stanza Not Acceptable.";
            break;

        case StanzaError::StanzaErrorNotAllowed:
            cout << "Action not Allowed.";
            break;

        case StanzaError::StanzaErrorNotAuthorized:
            cout << "Action not authorized.";
            break;

        case StanzaError::StanzaErrorNotModified:
            cout << "Item not modified.";
            break;

        case StanzaError::StanzaErrorPaymentRequired:
            cout << "Payment required.";
            break;

        case StanzaError::StanzaErrorRecipientUnavailable:
            cout << "Recipient unavailable.";
            break;

        case StanzaError::StanzaErrorRedirect:
            cout << "Redirect.";
            break;

        case StanzaError::StanzaErrorRegistrationRequired:
            cout << "Registration required.";
            break;

        case StanzaError::StanzaErrorRemoteServerNotFound:
            cout << "Remote server not found";
            break;

        case StanzaError::StanzaErrorRemoteServerTimeout:
            cout << "Remote Server Timeout";
            break;

        case StanzaError::StanzaErrorResourceConstraint:
            cout << "Resource constraint";
            break;

        case StanzaError::StanzaErrorServiceUnavailable:
            cout << "Service unavailable.";
            break;

        case StanzaError::StanzaErrorSubscribtionRequired:
            cout << "Subscription required.";
            break;

        case StanzaError::StanzaErrorUndefinedCondition:
            cout << "Undefined condition";
            break;

        case StanzaError::StanzaErrorUnexpectedRequest:
            cout << "Unexpected request.";
            break;

        case StanzaError::StanzaErrorUnknownSender:
            cout << "Unknown sender.";
            break;

        case StanzaError::StanzaErrorUndefined:
            cout << "No stanza error occured";
            break;

        default:
            cout << "default-case.";
            break;
    }

    cout << std::endl;
}

void Channel::handleMUCInfo(gloox::MUCRoom* room, int features, const std::string& name, const gloox::DataForm* /*infoForm*/)
{
    // TODO: This is a stub. At least log that this method is being called.
    std::cout << "[" << room->name() << "] Room info: Features: " << features << " name: " << name << std::endl;
}

void Channel::handleMUCItems(gloox::MUCRoom* /*room*/, const gloox::Disco::ItemList& /*items*/)
{
    // TODO: This is a stub. At least log that this method is being called.
}

void Channel::speak(const std::string& message)
{
    room->send(message);
}

void Channel::join(gloox::Presence::PresenceType type, const std::string& status, int priority)
{
    room->join(type, status, priority);
}
