#include "Channel.h"

#include <iostream>

#include <gloox/mucroom.h>
#include <gloox/presence.h>
#include <gloox/message.h>
#include <gloox/jid.h>
#include <gloox/disco.h>
#include <gloox/presence.h>

using namespace std;
using namespace gloox;

Channel::Channel (BotCore & bot, Connection & connection) : lastSpoken ("AaardvarkappleSauceee!111!11@#$%!@"), connection (connection), bot (bot)
{
	// AaardvarkappleSauceee!111!11@#$%!@ is just something the bot would never say
}


Channel::~Channel ()
{
}

void Channel::handleMUCParticipantPresence (MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence)
{
	// TODO: This should query the plugins to see if they care to handle the event
	cout << "[" << room->name () << "] " << participant.nick->resource () << " ";
	Presence::PresenceType p = presence.subtype ();
	switch (p) {
	case gloox::Presence::Available:
		cout << "is online.";
		break;
	case gloox::Presence::Chat:
		cout << "is 'available for chat.'";
		break;
	case gloox::Presence::Away:
		cout << "went away.";
		break;
	case gloox::Presence::DND:
		cout << "went DND.";
		break;
	case gloox::Presence::XA:
		cout << "went XA.";
		break;
	case gloox::Presence::Unavailable:
		cout << "went offline.";
		break;
	case gloox::Presence::Probe:
		cout << "== Presence probe ==";
		break;
	case gloox::Presence::Error:
		cout << "== Presence error ==";
		break;
	case gloox::Presence::Invalid:
		cout << "== The stanza is invalid ==";
		break;
	default:
		cout << "== default presence handling ==";
		break;
	}
	cout << endl;
}

void Channel::handleMUCMessage (MUCRoom* room, const Message& msg, bool priv)
{
	if (msg.body () == lastSpoken) {
		// Ignore it. This is the message we just sent.
	}
	else {
		// TODO: Log
		cout << "[" << room->name () << ": " << msg.from ().resource () << "(" << priv << ") ]  " << msg.body () << endl;

		// TODO: React
		//bot.processMessage (room, msg, priv);

		speak (room, "Tell me more about " + msg.body () + ", " + msg.from ().resource ());
	}
}

bool Channel::handleMUCRoomCreation (MUCRoom* room)
{
	// TODO: Stub. What does scenario does this handle and would plugins care?
	return true;
}

void Channel::handleMUCSubject (MUCRoom* room, const std::string &nick, const std::string &subject)
{
	cout << room->name () << " Subject is \"" << subject << "\"";
	if (nick.empty ()) {
		// If no nick is given, then the topic was already set.
		cout << endl;
	}
	else {
		cout << " set by " << nick << endl;
	}
}

void Channel::handleMUCInviteDecline (MUCRoom* room, const JID& invitee, const std::string& reason)
{
	// TODO: Stub.
}

void Channel::handleMUCError (MUCRoom* room, StanzaError error)
{
	// TODO: Stub.
	cout << "[" << room->name () << "] Channel Error: ";
	switch (error) {
	case gloox::StanzaErrorBadRequest:
		cout << "Bad Request.";
		break;
	case gloox::StanzaErrorConflict:
		cout << "Conflict.";
		break;
	case gloox::StanzaErrorFeatureNotImplemented:
		cout << "Feature not implemented.";
		break;
	case gloox::StanzaErrorForbidden:
		cout << "Forbidden. ";
		break;
	case gloox::StanzaErrorGone:
		cout << "Gone.";
		break;
	case gloox::StanzaErrorInternalServerError:
		cout << "Internal server error.";
		break;
	case gloox::StanzaErrorItemNotFound:
		cout << "Item not found.";
		break;
	case gloox::StanzaErrorJidMalformed:
		cout << "JID Malformed.";
		break;
	case gloox::StanzaErrorNotAcceptable:
		cout << "Stanza Not Acceptable.";
		break;
	case gloox::StanzaErrorNotAllowed:
		cout << "Action not Allowed.";
		break;
	case gloox::StanzaErrorNotAuthorized:
		cout << "Action not authorized.";
		break;
	case gloox::StanzaErrorNotModified:
		cout << "Item not modified.";
		break;
	case gloox::StanzaErrorPaymentRequired:
		cout << "Payment required.";
		break;
	case gloox::StanzaErrorRecipientUnavailable:
		cout << "Recipient unavailable.";
		break;
	case gloox::StanzaErrorRedirect:
		cout << "Redirect.";
		break;
	case gloox::StanzaErrorRegistrationRequired:
		cout << "Registration required.";
		break;
	case gloox::StanzaErrorRemoteServerNotFound:
		cout << "Remote server not found";
		break;
	case gloox::StanzaErrorRemoteServerTimeout:
		cout << "Remote Server Timeout";
		break;
	case gloox::StanzaErrorResourceConstraint:
		cout << "Resource constraint";
		break;
	case gloox::StanzaErrorServiceUnavailable:
		cout << "Service unavailable.";
		break;
	case gloox::StanzaErrorSubscribtionRequired:
		cout << "Subscription required.";
		break;
	case gloox::StanzaErrorUndefinedCondition:
		cout << "Undefined condition";
		break;
	case gloox::StanzaErrorUnexpectedRequest:
		cout << "Unexpected request.";
		break;
	case gloox::StanzaErrorUnknownSender:
		cout << "Unknown sender.";
		break;
	case gloox::StanzaErrorUndefined:
		cout << "No stanza error occured";
		break;
	default:
		cout << "default-case.";
		break;
	}
	cout << endl;
}

void Channel::handleMUCInfo (MUCRoom* room, int features, const std::string &name, const DataForm *infoForm)
{
	// TODO: Stub.
	cout << "[" << room->name () << "] Room info: Features: " << features << " name: " << name << endl;
}

void Channel::handleMUCItems (MUCRoom *room, const Disco::ItemList &items)
{
	// TODO: Stub.
}

void Channel::speak (MUCRoom * room, const string & message)
{
	lastSpoken = message;
	room->send (message);
}
