#pragma once
#include"Resource.h"

class puruAnim;

class Resource_Animation : public Resource
{
public:
	Resource_Animation();
	Resource_Animation(const Resource_Animation& _resAnim);
	~Resource_Animation();

	Resource_Animation& operator=(const Resource_Animation& resAnim);

	puruAnim* GetResource();

	bool LoadResource(puruAnim* _anim);
	bool LoadResource(std::string texName, int nFrames, float nFPS, float tx, float ty, float width, float height);

	void Play();
	void Stop();
	void Update(float _dt);
	void SetLoopMode(bool loop);
	bool IsPlaying();

private:
	puruAnim* m_resource{ nullptr };

};