#include"GraphicsManager.h"
#include"GameStateManager.h"
#include"ResourceManager.h"
#include"Resource_Animation.h"
#include"Resource_Sprite.h"
#include"Resource_Font.h"

#include <puruAnim.h>
#include <puruQuad.h>
#include <puruSprite.h>
#include <puruFont.h>

GraphicsManager* GraphicsManager::m_graphicsManagerInstance{ nullptr };

GraphicsManager::GraphicsManager() : Singleton(), m_pge(nullptr), m_gui(nullptr)
{

}

GraphicsManager::GraphicsManager(const GraphicsManager &)
{
}

GraphicsManager & GraphicsManager::operator=(const GraphicsManager &)
{
	// TODO: insert return statement here
	return *this;
}

GraphicsManager::~GraphicsManager()
{
	ResetGUI();
	m_pge = nullptr;
}

void GraphicsManager::DestroyInstance()
{
	if (m_graphicsManagerInstance)
		delete m_graphicsManagerInstance;
	m_graphicsManagerInstance = nullptr;
}

bool GraphicsManager::Initialize(PuruGameSystem* _pge)
{
	bool result = false;
	m_pge = _pge;

	if (!m_pge)
	{
		return false;
	}

	return true;
}

void GraphicsManager::BeginScene()
{
	m_pge->Gfx_BeginScene(0);
}

void GraphicsManager::EndScene()
{
	m_pge->Gfx_EndScene();
}

void GraphicsManager::Render(puruQuad& _quad)
{
	RenderFunc(_quad);
}

void GraphicsManager::Render(Resource_Animation * _resAnim, float _x, float _y)
{
	RenderFunc(_resAnim->GetResource(), _x, _y);
}

void GraphicsManager::Render(Resource_Sprite * _resSprite, float _x, float _y)
{
	RenderFunc(_resSprite->GetResource(), _x, _y);
}

void GraphicsManager::Render(Resource_Font* _resFont, float _x, float _y, char* _message, float red, float green, float blue, float _alpha)
{
	RenderFunc(_resFont->GetResource(), _x, _y, _message, red, green, blue, _alpha);
}

void GraphicsManager::Render(Resource_Font* _resFont, float _x, float _y, const char* _message, float red, float green, float blue, float _alpha)
{
	char* cmessage = const_cast<char*>(_message);
	Render(_resFont, _x, _y, cmessage);
}



GraphicsManager * GraphicsManager::GetInstance()
{
	if (!m_graphicsManagerInstance) {
		m_cs.Lock();
		if (!m_graphicsManagerInstance)
			m_graphicsManagerInstance = new GraphicsManager();
		m_cs.Unlock();
	}
	return m_graphicsManagerInstance;
}

void GraphicsManager::RenderFunc(puruQuad& _quad)
{
	_quad.RenderQuad();
}

void GraphicsManager::RenderFunc(puruSprite * _spr, float _x, float _y)
{
	_spr->Render(_x, _y, Globals::WORLD_SCALE);
}

void GraphicsManager::RenderFunc(puruAnim * _anim, float _x, float _y)
{
	_anim->Render(_x, _y, Globals::WORLD_SCALE);
}

void GraphicsManager::RenderFunc(puruFont* _fnt, float _x, float _y, char* _message, float red, float green, float blue, float _alpha)
{
	_fnt->printf(_x, _y, _message);
}

void GraphicsManager::RenderFunc(puruFont* _fnt, float _x, float _y, const char* _message, float red, float green, float blue, float _alpha)
{
	char* cmessage = const_cast<char*>(_message);
	RenderFunc(_fnt, _x, _y, cmessage, red, green, blue, _alpha);
}

void GraphicsManager::RenderGUI()
{
	if (m_gui)
	{
		m_gui->Render();
	}
}

puruGUI * GraphicsManager::GetGUI()
{
	if (!m_gui)
	{
		m_cs.Lock();
		if (!m_gui)
		{
			m_gui = new puruGUI();
			m_gui->Initialize(m_pge);
		}
		m_cs.Unlock();
	}
	return m_gui;
}

void GraphicsManager::ResetGUI()
{
	if (m_gui)
	{
		m_gui->Shutdown();
		delete m_gui;
		m_gui = nullptr;
	}
}

