#pragma once
#include"Singleton.h"

class Resource_Audio;

class AudioManager : public Singleton
{
private:

	AudioManager();
	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);
	static AudioManager* m_audioManagerInstance;

public:
	static AudioManager* GetInstance();
	~AudioManager();
	void DestroyInstance();

	void PlaySoundEffect(Resource_Audio* _resAudio);

};