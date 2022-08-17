#include"ResourceManager.h"
#include"GameManager.h"
#include"Resource_Audio.h"
#include"Resource_Font.h"
#include"Resource_LevelPositions.h"
#include"Resource_Sprite.h"
#include"Resource_Texture.h"
#include"Resource_Animation.h"
#include<sstream>

bool ResourceManager::Initiate()
{
	bool result = false;
	result = LoadFile("Resources.txt");
	//m_handleLoadThread = CreateThread(NULL, 0, LoadResources, this, 0, NULL);
	LoadResources();
	return result;
}

ResourceManager::~ ResourceManager()
{
	//ShutDown();
	ClearResources();
}

void ResourceManager::ShutDown()
{
	WaitForSingleObject(m_handleLoadThread, INFINITE);
	CloseHandle(m_handleLoadThread);
}

bool ResourceManager::LoadFile(std::string fileName) {
	 if (m_inFile) {
		 m_inFile->close();
		 delete m_inFile;
		 m_inFile = nullptr;
	 }
	 m_inFile = new std::ifstream(fileName, std::ios::in);
	 if (!m_inFile)
	 {
		 return false;
	 }
	 return true;
 }

DWORD ResourceManager::LoadResources(LPVOID lpParam)
 {
	 ResourceManager* resourceManager = (ResourceManager*)lpParam;
	 while ((*resourceManager->m_inFile)) {
		 char cType;
		 (*resourceManager->m_inFile) >> cType;
		 if (cType != 'A' && cType != 'G' && cType != 'F' && cType != 'L') {
			 std::getline((*resourceManager->m_inFile), resourceManager->m_strLine);
			 continue;
		 }
		 switch(cType) {
			 case 'A':
				 resourceManager->LoadAudio();
				 break;
			 case 'G':
				 resourceManager->LoadGraphics();
				 break;
			 case 'F':
				 resourceManager->LoadFont();
				 break;
			 case 'L':
				 resourceManager->LoadLevel();
				 break;
			 default:
				 break;
		 }
	 }

	 resourceManager->m_inFile->close();
	 delete resourceManager->m_inFile;
	 resourceManager->m_inFile = nullptr;
	 return 0;
 }

void ResourceManager::LoadResources()
{

	while ((*m_inFile)) {
		char cType;
		(*m_inFile) >> cType;
		if (cType != 'A' && cType != 'G' && cType != 'F' && cType != 'L') {
			std::getline((*m_inFile), m_strLine);
			continue;
		}
		switch (cType) {
		case 'A':
			LoadAudio();
			break;
		case 'G':
			LoadGraphics();
			break;
		case 'F':
			LoadFont();
			break;
		case 'L':
			LoadLevel();
			break;
		default:
			break;
		}
	}

	m_inFile->close();
	delete m_inFile;
	m_inFile = nullptr;
}

void ResourceManager::ClearResources()
 {
	 std::map<std::string, Resource_Wrapper*>::iterator itMap = m_mapResources.begin();
	 while (itMap != m_mapResources.end()) {
		 delete itMap->second;
		 itMap = m_mapResources.erase(itMap);
	 }
 }

void ResourceManager::LoadAudio()
 {
	 std::string fileName, audioName;
	 (*m_inFile) >> fileName >> audioName;
	 Resource_Audio* resource = new Resource_Audio();
	 if (resource->LoadResource(fileName))
	 {
		 InsertResource(audioName, Resource_Type::RESOURCE_AUDIO, resource);
	 }
	 else
	 {
		 delete resource;
	 }
 }

void ResourceManager::LoadGraphics()
 {
	 int gType;
	 (*m_inFile) >> gType;
	 switch (gType) {
	 case 1:
		 LoadTexture();
		 break;
	 case 2:
		 LoadSprite();
		 break;
	 case 3:
		 LoadAnimation();
		 break;
	 default:
		 break;
	 }
 }

void ResourceManager::LoadLevel()
{
	int type, level, prevlevel = 0;
	float x, y;
	char c = ' ';

	std::vector<std::pair<int, Globals::Position>>* vecLevelResource =  new std::vector<std::pair<int, Globals::Position>>;

	(*m_inFile) >> level;
	prevlevel = level;
	while ((*m_inFile)) {
		if (level == 0) {
			(*m_inFile) >> x >> y;
			type = 0;
		}
		else
			(*m_inFile) >> type >> x >> y;

		if (prevlevel != level) {
			std::stringstream ss;
			ss << "Level" << prevlevel;
			Resource_LevelPositions* resource = new Resource_LevelPositions();
			if (resource->LoadResource(vecLevelResource))
			{
				InsertResource(ss.str(), Resource_Type::RESOURCE_LEVELPOSITIONS, resource);
			}
			else
			{
				delete resource;
			}
			vecLevelResource = nullptr;
			vecLevelResource = new std::vector<std::pair<int, Globals::Position>>;
			vecLevelResource->clear();
			prevlevel = level;
		}
		vecLevelResource->push_back(std::pair<int, Globals::Position>(type, Globals::Position(x, y)));
		(*m_inFile) >> c >> level;
	}
	std::stringstream ss;
	ss << "Level" << prevlevel;
	Resource* resource = new Resource_LevelPositions(vecLevelResource);
	InsertResource(ss.str(), Resource_Type::RESOURCE_LEVELPOSITIONS, resource);
	vecLevelResource = nullptr;
	vecLevelResource = new std::vector<std::pair<int, Globals::Position>>;
}

void ResourceManager::LoadFont()
{
	std::string fontDataFilename, textureFilename, fontName;
	(*m_inFile) >> fontDataFilename >> textureFilename >> fontName;
	Resource_Font* resource = new Resource_Font();
	if (resource->LoadResource(fontDataFilename.c_str(), textureFilename.c_str()))
	{
		InsertResource(fontName, Resource_Type::RESOURCE_FONT, resource);
	}
	else
	{
		delete resource;
	}
}

void ResourceManager::LoadTexture()
 {
	 std::string fileName, texName;
	 int width, height;
	 (*m_inFile) >> width >> height >> fileName >> texName;
	 Resource_Texture* resource = new Resource_Texture();
	 if (resource->LoadResource(fileName.c_str(), width, height))
	 {
		 InsertResource(texName, Resource_Type::RESOURCE_TEXTURE, resource);
	 }
	 else
	 {
		 delete resource;
	 }
 }

void ResourceManager::LoadSprite()
{
	float tx, ty, width, height;
	std::string texName, sprName;

	(*m_inFile) >> tx >> ty >> width >> height >> texName >> sprName;
	Resource_Sprite* resource = new Resource_Sprite();
	if (resource->LoadResource(texName, tx, ty, width, height))
	{
		InsertResource(sprName, Resource_Type::RESOURCE_SPRITE, resource);
	}
	else
	{
		delete resource;
	}
	return;
}

void ResourceManager::LoadAnimation()
{
	int nFrames;
	float nFPS, tx, ty, width, height;
	std::string texName, animName;

	(*m_inFile) >> nFrames >> nFPS >> tx >> ty >> width >> height >> texName >> animName;
	Resource_Animation* resource = new Resource_Animation;
	if (resource->LoadResource(texName, nFrames, nFPS, tx, ty, width, height))
	{
		InsertResource(animName, Resource_Type::RESOURCE_ANIMATION, resource);
	}
	else
	{
		delete resource;
	}
	return;
}

void ResourceManager::InsertResource(const std::string _resourceName, Resource_Type _resType, Resource* _resource)
{
	Resource_Wrapper* resWrap = new Resource_Wrapper(_resType, _resource);
	m_mapResources[_resourceName] = resWrap;
	/*m_mapResources.insert(std::pair<std::string, Resource_Wrapper*>(_resourceName, resWrap));*/
}

Resource_Wrapper* ResourceManager::RetrieveResourceWrapper(std::string resourceName)
{
	if (m_mapResources.find(resourceName) != m_mapResources.end())
		return m_mapResources[resourceName];
	else 
		return nullptr;
}



 