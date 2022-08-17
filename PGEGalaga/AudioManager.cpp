#include"AudioManager.h"
#include"ResourceManager.h"
#include"GameManager.h"
#include"Resource_Audio.h"

#include <puruSound.h>

void AudioManager::PlaySoundEffect(Resource_Audio * _resAudio)
{
	puruSound* snd = _resAudio->GetResource();
	snd->Play();
}


