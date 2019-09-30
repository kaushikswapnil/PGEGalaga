#pragma once
#include"Resource.h"

class puruSound;

class Resource_Audio : public Resource
{
public:
	Resource_Audio();
	Resource_Audio(puruSound* _snd);
	Resource_Audio(const Resource_Audio& _resAudio) = delete;
	~Resource_Audio();

	Resource_Audio& operator=(const Resource_Audio& resAudio) = delete;

	puruSound* GetResource();

	bool LoadResource(puruSound* _snd);
	bool LoadResource(std::string fileName);

	void Play();

private:
	puruSound* m_resource{ nullptr };
};
