#pragma once
#include"Resource.h"

class puruSprite;

class Resource_Sprite : public Resource
{
public:
	Resource_Sprite();
	Resource_Sprite(puruSprite* _sprite);
	Resource_Sprite(const Resource_Sprite& _resSprite);
	~Resource_Sprite();

	puruSprite* GetResource();

	bool LoadResource(puruSprite* _sprite);
	bool LoadResource(std::string texName, float tx, float ty, float width, float height);

private:
	puruSprite* m_resource{ nullptr };
};

