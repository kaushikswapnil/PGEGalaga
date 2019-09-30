#include"Resource_Sprite.h"
#include"Resource_Texture.h"
#include"ResourceManager.h"
#include <puruSprite.h>

Resource_Sprite::Resource_Sprite() : Resource()
{
}

Resource_Sprite::Resource_Sprite(puruSprite * _sprite) : Resource(), m_resource(_sprite)
{
}

Resource_Sprite::Resource_Sprite(const Resource_Sprite & _resSprite) : Resource()
{
	if (m_resource)
	{
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
	m_resource = new puruSprite(*_resSprite.m_resource);
}

Resource_Sprite::~Resource_Sprite()
{
	if (m_resource) {
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
}

puruSprite * Resource_Sprite::GetResource()
{
	return m_resource;
}

bool Resource_Sprite::LoadResource(puruSprite* _sprite)
{
	m_resource = _sprite;
	return true;
}

bool Resource_Sprite::LoadResource(std::string texName, float tx, float ty, float width, float height)
{
	bool result;
	Resource_Texture* texResource = ResourceManager::GetInstance()->RetrieveResourceWrapper(texName)->GetResourceContainer<Resource_Texture>();
	if (!texResource) {
		return false;
	}
	m_resource = new puruSprite();
	if (!m_resource)
	{
		return false;
	}

	result = m_resource->Initialize(tx, ty, width, height, texResource->GetResource());
	if (!result)
	{
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
		return false;
	}
	return true;
}

