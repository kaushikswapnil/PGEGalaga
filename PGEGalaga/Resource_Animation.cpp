#include "Resource_Animation.h"
#include"Resource_Texture.h"
#include"ResourceManager.h"
#include <puruAnim.h>

Resource_Animation::Resource_Animation() : Resource()
{
}

Resource_Animation::Resource_Animation(const Resource_Animation & _resAnim) : Resource()
{
	m_resource = new puruAnim(*_resAnim.m_resource);
}

Resource_Animation::~Resource_Animation()
{
	if (m_resource) {
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
}

Resource_Animation & Resource_Animation::operator=(const Resource_Animation & resAnim)
{
	m_resource = new puruAnim(*resAnim.m_resource);
	return *this;
}

puruAnim * Resource_Animation::GetResource()
{
	return m_resource;
}

bool Resource_Animation::LoadResource(puruAnim * _anim)
{
	if (!_anim)
	{
		return false;
	}
	if (m_resource)
	{
		m_resource->Shutdown();
		delete m_resource;
		m_resource = nullptr;
	}
	m_resource = _anim;
	return true;
}

bool Resource_Animation::LoadResource(std::string texName, int nFrames, float nFPS, float tx, float ty, float width, float height)
{
	Resource_Texture* texResource = ResourceManager::GetInstance()->RetrieveResourceWrapper(texName)->GetResourceContainer<Resource_Texture>();
	if (!texResource)
	{
		return false;
	}
	m_resource = new puruAnim(nFrames, nFPS, tx, ty, width, height, texResource->GetResource());
	if (!m_resource)
	{
		return false;
	}
	return true;
}

void Resource_Animation::Play()
{
	if (m_resource)
		m_resource->Play();
}

void Resource_Animation::Stop()
{
	if (m_resource)
		m_resource->Stop();
}

void Resource_Animation::Update(float _dt)
{
	if (m_resource)
		m_resource->Update(_dt);
}

void Resource_Animation::SetLoopMode(bool loop)
{
	if (m_resource)
		m_resource->SetLoopMode(loop);
}

bool Resource_Animation::IsPlaying()
{
	if (m_resource)
		return m_resource->IsPlaying();
	return false;
}
