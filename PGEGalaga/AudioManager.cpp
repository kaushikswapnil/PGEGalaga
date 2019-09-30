#include"AudioManager.h"
#include"ResourceManager.h"
#include"GameManager.h"
#include"Resource_Audio.h"

#include <puruSound.h>

AudioManager* AudioManager::m_audioManagerInstance{ nullptr };

AudioManager::AudioManager() : Singleton()
{
}

AudioManager::AudioManager(const AudioManager &)
{
}

AudioManager & AudioManager::operator=(const AudioManager &)
{
	// TODO: insert return statement here
	return *this;
}

AudioManager * AudioManager::GetInstance()
{
	if (!m_audioManagerInstance) {
		m_cs.Lock();
		if (!m_audioManagerInstance)
			m_audioManagerInstance = new AudioManager();
		m_cs.Unlock();
	}
	return m_audioManagerInstance;
}

AudioManager::~AudioManager()
{
}

void AudioManager::DestroyInstance()
{
	if (m_audioManagerInstance)
		delete m_audioManagerInstance;
	m_audioManagerInstance = nullptr;
}

void AudioManager::PlaySoundEffect(Resource_Audio * _resAudio)
{
	puruSound* snd = _resAudio->GetResource();
	snd->Play();
}


