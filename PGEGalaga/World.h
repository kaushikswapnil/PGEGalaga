#pragma once
#include"WorldEntity.h"
#include"Singleton.h"

class World : public Singleton{
private:
	World();
	World(const World&);
	World& operator=(const World&);
	static World* m_worldInstance;

	bool m_bGameWon{ false };
	int m_score{ 0 };
	int m_currentLevel{ 1 };
	int m_playerHealth{ 4 };
	long long m_lastLevelLoadTime{ 0 };
	long long m_nextLevelLoadTime{ 0 };
	long long m_lastScoreUpdateTime{ 0 };

	std::vector<WorldEntity*> m_worldEntities{};

public:
	~World();
	static World* GetInstance();
	static void DestroyInstance();

	void LoadLevel();
	void DestroyDeletedObjects();

	int GetScore();
	void SetScore(int _score);

	int GetPlayerHealth() const { return m_playerHealth; }
	void SetPlayerHealth(int val) { m_playerHealth = val; }

	long long GetLastScoreUpdateTime();
	void SetLastScoreUpdateTime(long long _time);

	void UpdateScore();

	void Update(float dt);
	void Render();

	void AddObjectToWorld(WorldEntity* _worldEntity);
	std::vector<WorldEntity*>& GetWorldEntityVector();

	int GetWorldEntityVectorSize();
};