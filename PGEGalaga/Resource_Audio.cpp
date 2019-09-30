#include"Resource_Audio.h"
#include"GameManager.h"
#include <puruSound.h>

Resource_Audio::Resource_Audio() : Resource()
{
}

Resource_Audio::Resource_Audio(puruSound * _snd) : Resource(), m_resource(_snd)
{
}

Resource_Audio::~Resource_Audio()
{
	if (m_resource) {
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
}

puruSound * Resource_Audio::GetResource()
{
	return m_resource;
}

bool Resource_Audio::LoadResource(puruSound * _snd)
{
	if (!_snd)
	{
		return false;
	}
	m_resource = _snd;
	return true;
}

bool Resource_Audio::LoadResource(std::string fileName)
{
	bool result;
	m_resource = new puruSound();
	if (!m_resource)
	{
		return false;
	}
	result = m_resource->Initialize(fileName.c_str());
	if (!result)
	{
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
		return false;
	}

	m_resource->Play();
	return true;
}

void Resource_Audio::Play()
{
	if (m_resource)
	{
		m_resource->Play();
	}
}
