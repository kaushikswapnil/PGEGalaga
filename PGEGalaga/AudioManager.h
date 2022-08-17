#pragma once
#include"Singleton.h"

class Resource_Audio;

class AudioManager : public Singleton<AudioManager>
{
private:

public:
	void PlaySoundEffect(Resource_Audio* _resAudio);

};