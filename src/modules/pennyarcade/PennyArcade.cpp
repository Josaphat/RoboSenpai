#include "PennyArcade.h"

#include <iostream>
#include <gloox/message.h>

#include "../../Channel.h"

// Initialize the module (which automatically adds it to the std::map in Module.h
PennyArcade pa ("PennyArcade");

PennyArcade::PennyArcade (const std::string & name) : Module (name)
{
}


PennyArcade::~PennyArcade ()
{
}

void PennyArcade::accept (Channel * src, const gloox::Message & msg)
{
	// TODO: Actually implement the plugin
	const std::string text = msg.body ();
	if (text.compare ("!pa") == 0) {
		src->speak ("I am the latest penny arcade comic");
	}
	else {
		// nothing.
	}
}