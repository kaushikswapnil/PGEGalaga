#include "stdafx.h"
#include "LevelManager.h"
#include"Player.h"
#include"Enemy.h"
#include"Resource_LevelPositions.h"
#include<sstream>

void LevelManager::LoadLevel(long long nextLevelLoadTime, int level, std::vector<WorldEntity*>& worldEntities)
{
	std::vector<std::pair<int, Globals::Position>> levelPositions;
	std::stringstream ss;
	WorldEntity* worldEntity;
	if (nextLevelLoadTime == 0)
	{
		ss.str(std::string(""));
		ss << "Level" << 0;
		levelPositions = *ResourceManager::GetInstance()->RetrieveResourceWrapper(ss.str())->GetResourceContainer<Resource_LevelPositions>()->GetResource();
		std::vector<std::pair<int, Globals::Position>>::iterator itlevelpos = levelPositions.begin();
		while (itlevelpos != levelPositions.end())
		{
			LoadEntity(worldEntity, (*itlevelpos).first, (*itlevelpos).second);
			worldEntities.push_back(worldEntity);
			++itlevelpos;
		}
		levelPositions.clear();
	}
	if (nextLevelLoadTime < Globals::MyGetTime())
	{
		ss.str(std::string(""));
		ss << "Level" << level;
		levelPositions = *ResourceManager::GetInstance()->RetrieveResourceWrapper(ss.str())->GetResourceContainer<Resource_LevelPositions>()->GetResource();
		std::vector<std::pair<int, Globals::Position>>::iterator itlevelpos = levelPositions.begin();
		while (itlevelpos != levelPositions.end())
		{
			LoadEntity(worldEntity, (*itlevelpos).first, (*itlevelpos).second);
			worldEntities.push_back(worldEntity);
			++itlevelpos;
		}
	}
}

void LevelManager::LoadEntity(WorldEntity *& worldEntity, int type, Globals::Position position)
{
	if (type == 0)
	{
		worldEntity = new Player(position);
	}
	else
	{
		worldEntity = new Enemy(type, position);
	}
	return;
}
