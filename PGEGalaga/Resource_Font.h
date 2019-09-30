#pragma once
#include"Resource.h"

class puruFont;

class Resource_Font : public Resource
{
public:
	Resource_Font();
	Resource_Font(puruFont* _fnt);
	~Resource_Font();
	
	puruFont* GetResource();

	bool LoadResource(puruFont* _fnt);
	bool LoadResource(char* fontDataFilename, char* textureFilename);
	bool LoadResource(const char* fontDataFilename, const char* textureFilename);

private:
	puruFont* m_resource{ nullptr };
};
