#pragma once
#include"Resource_Wrapper.h"
#include"Resource_Audio.h"
#include"Resource_Font.h"
#include"Resource_LevelPositions.h"
#include"Resource_Sprite.h"
#include"Resource_Texture.h"
#include"Resource_Animation.h"

Resource_Wrapper::Resource_Wrapper() : m_resourceContainer{nullptr}, m_type{RESOURCE_NULL}
{
}

Resource_Wrapper::~Resource_Wrapper()
{
	if (m_type == Resource_Type::RESOURCE_ANIMATION) {
		Resource_Animation* resPtr = GetResourceContainer<Resource_Animation>();
		if (resPtr)
			delete resPtr;
	}
	else if (m_type == Resource_Type::RESOURCE_AUDIO) {
		Resource_Audio* resPtr = GetResourceContainer<Resource_Audio>();
		if (resPtr)
			delete resPtr;
	}
	else if (m_type == Resource_Type::RESOURCE_FONT) {
		Resource_Font* resPtr = GetResourceContainer<Resource_Font>();
		if (resPtr)
			delete resPtr;
	}
	else if (m_type == Resource_Type::RESOURCE_LEVELPOSITIONS) {
		Resource_LevelPositions* resPtr = GetResourceContainer<Resource_LevelPositions>();
		if (resPtr)
			delete resPtr;
	}
	else if (m_type == Resource_Type::RESOURCE_SPRITE) {
		Resource_Sprite* resPtr = GetResourceContainer<Resource_Sprite>();
		if (resPtr)
			delete resPtr;
	}
	else if (m_type == Resource_Type::RESOURCE_TEXTURE) {
		Resource_Texture* resPtr = GetResourceContainer<Resource_Texture>();
		if (resPtr)
			delete resPtr;
	}
	m_resourceContainer = nullptr;
}

Resource_Wrapper::Resource_Wrapper(Resource_Type _resType, Resource* _resource) : m_type(_resType), m_resourceContainer(_resource)
{
}

Resource_Wrapper::Resource_Wrapper(const Resource_Wrapper & _resWrap)
{
	*m_resourceContainer = *_resWrap.m_resourceContainer;
	m_type = _resWrap.m_type;
}

void Resource_Wrapper::LoadResource(Resource_Type _type, Resource* _resource)
{
	m_type = _type;
	m_resourceContainer = _resource;
}

template<typename R>
R* Resource_Wrapper::GetResourceContainer() {
R* ptr = static_cast<R*>(m_resourceContainer);
return ptr;
};

template Resource_Animation* Resource_Wrapper::GetResourceContainer<Resource_Animation>();
template Resource_Audio* Resource_Wrapper::GetResourceContainer<Resource_Audio>();
template Resource_Font* Resource_Wrapper::GetResourceContainer<Resource_Font>();
template Resource_LevelPositions* Resource_Wrapper::GetResourceContainer<Resource_LevelPositions>();
template Resource_Sprite* Resource_Wrapper::GetResourceContainer<Resource_Sprite>();
template Resource_Texture* Resource_Wrapper::GetResourceContainer<Resource_Texture>();

