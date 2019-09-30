#pragma once
#include"Resource.h"
#include"GameManager.h"
#include <string>

class puruTexture;

class Resource_Texture : public Resource
{
public:
	Resource_Texture();
	Resource_Texture(puruTexture* _tex);
	Resource_Texture(const Resource_Texture& _resTex) = delete;
	~Resource_Texture();

	Resource_Texture& operator=(const Resource_Texture& other) = delete;

	puruTexture* GetResource();

	bool LoadResource(puruTexture* _resource);
	bool LoadResource(std::string fileName, int width, int height);

private:
	puruTexture* m_resource{ nullptr };
};
