#pragma once
#include"GameManager.h"

#include <puruGUI.h>
#include<map>

class Resource_Animation;
class Resource_Sprite;
class Resource_Font;

class puruFont;
class puruAnim;
class puruQuad;
class puruSprite;

class GraphicsManager : public Singleton
{
private:

	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	GraphicsManager& operator=(const GraphicsManager&);

	static GraphicsManager* m_graphicsManagerInstance;

	puruGUI *m_gui{ nullptr };
	PuruGameSystem* m_pge;


public:
	static GraphicsManager* GetInstance();
	~GraphicsManager();
	static void DestroyInstance();

	bool Initialize(PuruGameSystem* _pge);

	void BeginScene();
	void EndScene();

	void Render(puruQuad& _quad);

	void Render(Resource_Animation* _resAnim, float _x, float _y);

	void Render(Resource_Sprite* _resSprite, float _x, float _y);

	void Render(Resource_Font* _resFont, float _x, float _y, char* _message, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float _alpha = 1.0f);
	void Render(Resource_Font* _resFont, float _x, float _y, const char* _message, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float _alpha = 1.0f);

	void RenderGUI();
	puruGUI * GetGUI();
	void ResetGUI();

private:
	void RenderFunc(puruQuad& _quad);
	void RenderFunc(puruSprite* _spr, float _x, float _y);
	void RenderFunc(puruAnim* _anim, float _x, float _y);
	void RenderFunc(puruFont* _fnt, float _x, float _y, char* _message, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float _alpha = 1.0f);
	void RenderFunc(puruFont* _fnt, float _x, float _y, const char* _message, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float _alpha = 1.0f);
};
