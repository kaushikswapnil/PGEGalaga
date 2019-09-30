#include "Resource_Font.h"
#include <puruFont.h>

Resource_Font::Resource_Font() : Resource()
{
}

Resource_Font::Resource_Font(puruFont * _fnt) : Resource(), m_resource(_fnt)
{
}

Resource_Font::~Resource_Font()
{
	if (m_resource) {
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
}

puruFont * Resource_Font::GetResource()
{
	return m_resource;
}

bool Resource_Font::LoadResource(puruFont * _fnt)
{
	if (!_fnt)
	{
		return false;
	}
	m_resource = _fnt;
	return true;
}

bool Resource_Font::LoadResource(char* fontDataFilename, char* textureFilename)
{
	bool result;

	m_resource = new puruFont();
	if (!m_resource)
	{
		return false;
	}

	result = m_resource->Initialize(fontDataFilename, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

bool Resource_Font::LoadResource(const char* fontDataFilename, const char* textureFilename)
{
	char* cFontDataFilename = const_cast<char*>(fontDataFilename);
	char* cTextureFilename = const_cast<char*>(textureFilename);
	return LoadResource(cFontDataFilename, cTextureFilename);
}