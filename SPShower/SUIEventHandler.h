#pragma once
#include "SUIEvent.h"

using namespace SPEngine;

class SUIEventHandler
{
public:
	virtual bool Function(SUIEventPtr e) = 0;
};

typedef SPPointer<SUIEventHandler> SUIEventHandlerPtr;