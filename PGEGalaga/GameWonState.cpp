#include"GameWonState.h"
#include"ResourceManager.h"
#include"GraphicsManager.h"
#include"GameStateManager.h"
#include"InputManager.h"
#include"Resource_Audio.h"
#include"Resource_Font.h"
#include"Resource_Texture.h"
#include"Resource_Sprite.h"
#include<sstream>
#include<iomanip>

#include <puruGUI.h>

GameWonState::GameWonState()
{
}

GameWonState::~GameWonState()
{
}

void GameWonState::ListenToEvent(Event * _event)
{
	Input_KeyEvent* inpEvent = dynamic_cast<Input_KeyEvent*>(_event);
	if (inpEvent)
		HandleInput(inpEvent);
}

void GameWonState::HandleInput(Input_KeyEvent* _keyEvent)
{
	if (_keyEvent->GetVirtualKey() == PGEK_ESCAPE && _keyEvent->IsDown() == true) {
		GameStateManager::GetInstance()->ChangeState(Globals::GameStates::STATE_EXIT);
	}

	if (_keyEvent->GetVirtualKey() == PGEK_SPACE && _keyEvent->IsDown() == true) {
		GameStateManager::GetInstance()->ChangeState(Globals::GameStates::STATE_MAINMENU);
	}
}

void GameWonState::Render()
{
	GraphicsManager::GetInstance()->Render(m_quadBG);
	m_gui->Render();
	std::stringstream ss;
	ss << "dt: " << std::setprecision(3) << GameManager::GetInstance()->GetPGEPointer()->Timer_GetDelta() << "\nFPS: " << GameManager::GetInstance()->GetPGEPointer()->Fps_GetFPS();
	GraphicsManager::GetInstance()->Render(m_fnt, 5, 5, ss.str().c_str());
}

void GameWonState::Enter()
{
	Subscriber* sub = this;
	InputManager::GetInstance()->AddSubscriber(sub);

	m_gui = GraphicsManager::GetInstance()->GetGUI();

	InitializeBG();
	m_fnt = ResourceManager::GetInstance()->RetrieveResourceWrapper("Font1")->GetResourceContainer<Resource_Font>();
	m_sndMenu = ResourceManager::GetInstance()->RetrieveResourceWrapper("MenuSND")->GetResourceContainer<Resource_Audio>();
	m_sprCursor = ResourceManager::GetInstance()->RetrieveResourceWrapper("CursorSprite")->GetResourceContainer<Resource_Sprite>();

	m_menuHandler.LoadGameWonMenu(m_gui, m_fnt->GetResource(), m_sndMenu->GetResource(), m_sprCursor->GetResource());
}

void GameWonState::Exit()
{
	Subscriber* sub = this;
	InputManager::GetInstance()->RemoveSubscriber(sub);
	m_menuHandler.DeleteGameWonMenu(m_gui);

	GraphicsManager::GetInstance()->ResetGUI();
	m_gui = nullptr;
}

void GameWonState::Update(float dt)
{
	UpdateBG(dt);

	Globals::GameStates nextState = Globals::GameStates::STATE_NULL;
}

void GameWonState::UpdateBG(float dt)
{
	float tx, ty;
	static float t = 0.0f;

	t += dt;
	tx = 20 * cosf(t / 60);
	ty = 20 * sinf(t / 60);
}

void GameWonState::InitializeBG()
{
	Resource_Texture* tex = (ResourceManager::GetInstance()->RetrieveResourceWrapper("MenuBG")->GetResourceContainer<Resource_Texture>());

	m_quadBG.Initialize(tex->GetResource(), 0, 0, 800, 600);
}

