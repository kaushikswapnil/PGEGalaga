#pragma once
#include<fstream>
#include<map>
#include"Resource_Wrapper.h"
#include"Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
private:

	HANDLE m_handleLoadThread;

	std::string m_strLine;
	std::ifstream *m_inFile{ nullptr };

	std::map<std::string, Resource_Wrapper*> m_mapResources;

public:
	bool Initiate();
	~ResourceManager();
	void ShutDown();

	bool LoadFile(std::string fileName);
	static DWORD WINAPI LoadResources(LPVOID lpParam);

	void LoadResources();

	void LoadGraphics();

	void ClearResources();

	void LoadAudio();

	void LoadLevel();

	void LoadFont();

	void LoadTexture();

	void LoadSprite();

	void LoadAnimation();

	void InsertResource(const std::string _resourceName, Resource_Type _resType, Resource* _resource);

	Resource_Wrapper* RetrieveResourceWrapper(std::string resourceName);
};

