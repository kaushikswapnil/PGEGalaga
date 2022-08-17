#pragma once
#include"ResourceManager.h"	
#include"WorldEntity.h"

class LevelManager : public Singleton<LevelManager>
{
public:
	void LoadLevel(long long nextLevelLoadTime, int level, std::vector<WorldEntity*>& worldEntities);
	void LoadEntity(WorldEntity* &worldEntity, int type, Globals::Position position);
};

