#pragma once

#include <puruQuad.h>

#include"Input_KeyEvent.h"
#include"Subscriber.h"
#include "MenuHandler.h"

class Resource_Font;

class GameState : public Subscriber
{
public:
	GameState() { };
	virtual ~GameState() { };

	virtual void ListenToEvent(Event* _event) = 0;
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(float dt) = 0;

	virtual void UpdateBG(float dt) = 0;
	virtual void InitializeBG() = 0;

protected:
	MenuHandler m_menuHandler;
	puruQuad m_quadBG;
	Resource_Font* m_fnt{ 0 };
	puruGUI* m_gui{ nullptr };
};



