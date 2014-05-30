#pragma once

#include "../../Module.h"

class Channel;

class PennyArcade :
	public Module
{
public:
	PennyArcade (const std::string & name);
	virtual ~PennyArcade ();

public: // Override
	virtual void accept (Channel * src, const gloox::Message & msg);
};
