#pragma once
#include"ResourceManager.h"	
#include"WorldEntity.h"

class LevelManager : public Singleton
{
public:
	~LevelManager();

	static LevelManager* GetInstance();

	void LoadLevel(long long nextLevelLoadTime, int level, std::vector<WorldEntity*>& worldEntities);
	void LoadEntity(WorldEntity* &worldEntity, int type, Globals::Position position);

private:
	LevelManager();
	LevelManager(const LevelManager&);
	LevelManager& operator=(const LevelManager&);
	static LevelManager* m_levelManagerInstance;
};

