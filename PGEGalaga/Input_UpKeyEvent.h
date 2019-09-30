#pragma once
#include"Input_KeyEvent.h"

class Input_UpKeyEvent : public Input_KeyEvent
{
public:
	Input_UpKeyEvent(int _virtualkeycode) : Input_KeyEvent(_virtualkeycode) {};
	~Input_UpKeyEvent() {};

private:

};