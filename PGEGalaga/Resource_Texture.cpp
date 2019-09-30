#include"Resource_Texture.h"
#include <puruTexture.h>

Resource_Texture::Resource_Texture() : Resource()
{
}

Resource_Texture::Resource_Texture(puruTexture * _tex) : Resource(), m_resource(_tex)
{
}

Resource_Texture::~Resource_Texture()
{
	if (m_resource)
	{
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
}

puruTexture * Resource_Texture::GetResource()
{
	return m_resource;
}

bool Resource_Texture::LoadResource(puruTexture* _resource)
{
	if (!_resource)
	{
		return false;
	}
	
	m_resource = _resource;
	return true;
}

bool Resource_Texture::LoadResource(std::string fileName, int width, int height)
{
	bool result;

	std::wstring cWideStr = std::wstring(fileName.begin(), fileName.end());
	WCHAR* wideStr = const_cast<WCHAR*>(cWideStr.c_str());


	m_resource = new puruTexture();
	if (!m_resource)
	{
		return false;
	}
	
	result = m_resource->Initialize(wideStr, width, height);
	if (!result)
	{
		return false;
	}

	return true;
}
