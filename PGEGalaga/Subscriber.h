#pragma once
#include"Event.h"

class Subscriber {
public:
	virtual void ListenToEvent(Event* _event) = 0;
};