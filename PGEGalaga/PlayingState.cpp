#include"PlayingState.h"
#include"ResourceManager.h"
#include"GraphicsManager.h"
#include"GameStateManager.h"
#include"InputManager.h"
#include"Resource_Font.h"
#include"Resource_Texture.h"
#include"Resource_Sprite.h"
#include<sstream>
#include<iomanip>

PlayingState::PlayingState()
{
}

PlayingState::~PlayingState()
{
}

void PlayingState::ListenToEvent(Event * _event)
{
	Input_KeyEvent* inpEvent = dynamic_cast<Input_KeyEvent*>(_event);
	if (inpEvent)
		HandleInput(inpEvent);
}

void PlayingState::HandleInput(Input_KeyEvent* _keyEvent)
{
	if (_keyEvent->GetVirtualKey() == PGEK_ESCAPE && _keyEvent->IsDown() == true) {
		GameStateManager::GetInstance()->ChangeState(Globals::GameStates::STATE_EXIT);
	}
}

void PlayingState::Render()
{
	GraphicsManager::GetInstance()->Render(m_quadBG);
	m_world->Render();
	std::stringstream ss;
	ss << "Score: " << m_world->GetScore() << "\ndt: " << std::setprecision(3) << GameManager::GetInstance()->GetPGEPointer()->Timer_GetDelta() << "\nFPS: " << GameManager::GetInstance()->GetPGEPointer()->Fps_GetFPS() << "\nWorld Vector Size: " << m_world->GetWorldEntityVectorSize() << "\nGameScreen";
	GraphicsManager::GetInstance()->Render(m_fnt, 5, 5, ss.str().c_str());
}

void PlayingState::Enter()
{
	Subscriber* sub = this;
	InputManager::GetInstance()->AddSubscriber(sub);

	InitializeBG();
	m_fnt = ResourceManager::GetInstance()->RetrieveResourceWrapper("Font1")->GetResourceContainer<Resource_Font>();
	m_world = World::GetInstance();
}

void PlayingState::Exit()
{
	Subscriber* sub = this;
	InputManager::GetInstance()->RemoveSubscriber(sub);
	m_world->DestroyInstance();
	m_world = nullptr;
}

void PlayingState::Update(float dt)
{
	UpdateBG(dt);
	m_world->Update(dt);
}

void PlayingState::UpdateBG(float dt)
{
	float tx, ty;
	static float t = 0.0f;

	t += dt;
	tx = 20 * cosf(t / 60);
	ty = 20 * sinf(t / 60);
}

void PlayingState::InitializeBG()
{
	Resource_Texture* tex = (ResourceManager::GetInstance()->RetrieveResourceWrapper("GameBG")->GetResourceContainer<Resource_Texture>());

	m_quadBG.Initialize(tex->GetResource(), 0, 0, 800, 600);
}
