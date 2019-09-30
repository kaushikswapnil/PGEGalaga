#include "World.h"
#include"GraphicsManager.h"
#include"GameStateManager.h"
#include"ResourceManager.h"
#include"LevelManager.h"
#include"Resource_Sprite.h"
#include"Player.h"
#include"Enemy.h"
#include<sstream>

#include <time.h>

World* World::m_worldInstance{ nullptr };

World::World() 
{
	srand((unsigned int)time(NULL));
	LoadLevel();
}

World::World(const World &)
{
}

World & World::operator=(const World &)
{
	// TODO: insert return statement here
	return *this;
}


World::~World()
{
	std::vector<WorldEntity*>::iterator itWorldEntities = m_worldEntities.begin();
	while (itWorldEntities != m_worldEntities.end()) {
		delete (*itWorldEntities);
		itWorldEntities = m_worldEntities.erase(itWorldEntities);
	}
}

World * World::GetInstance()
{
	if (!m_worldInstance) {
		m_cs.Lock();
		if (!m_worldInstance)
			m_worldInstance = new World();
		m_cs.Unlock();
	}
	return m_worldInstance;
}

void World::DestroyInstance()
{
	if (m_worldInstance)
		delete m_worldInstance;
	m_worldInstance = nullptr;
}

void World::Update(float dt)
{
	//Loads level
	LoadLevel();

	unsigned int i = 0;
	while (i < m_worldEntities.size()) {
		m_worldEntities.at(i)->Update(dt);
		++i;
	}

	DestroyDeletedObjects();

	UpdateScore();

	//Check if game over and calls cleanup function
	if (!m_playerHealth) {
		GameStateManager::GetInstance()->ChangeState(Globals::GameStates::STATE_GAMEOVER);
	}
	else if(m_bGameWon)
		GameStateManager::GetInstance()->ChangeState(Globals::GameStates::STATE_GAMEWON);
}

void World::Render()
{

	unsigned int i = 0;
	while (i < m_worldEntities.size()) {
		m_worldEntities.at(i)->Render();
		++i;
	}

	//Render health icons
	Resource_Sprite* sprHealth = ResourceManager::GetInstance()->RetrieveResourceWrapper("PlayerSprite")->GetResourceContainer<Resource_Sprite>();
	for (int i = 0; i < m_playerHealth - 1; i++) {
		GraphicsManager::GetInstance()->Render(sprHealth, (float)(20 + (24 * i) + (8 * i)), 575.0f);
	}

}

void World::AddObjectToWorld(WorldEntity * _worldEntity)
{
	m_worldEntities.push_back(_worldEntity);
}

std::vector<WorldEntity*>& World::GetWorldEntityVector()
{
	return m_worldEntities;
}

int World::GetWorldEntityVectorSize()
{
	return m_worldEntities.size();
}

void World::LoadLevel() {
	if (m_lastLevelLoadTime == 0) {
		LevelManager::GetInstance()->LoadLevel(m_nextLevelLoadTime, m_currentLevel, m_worldEntities);
		m_lastLevelLoadTime = Globals::MyGetTime();
		m_nextLevelLoadTime = m_lastLevelLoadTime + (5000 * m_currentLevel);
	}
	else if ((m_nextLevelLoadTime < Globals::MyGetTime()) && (m_worldEntities.size() == 1)) { //Player also present
		++m_currentLevel;
		if (m_currentLevel <= Globals::MAX_LEVEL) {
			LevelManager::GetInstance()->LoadLevel(m_nextLevelLoadTime, m_currentLevel, m_worldEntities);
			m_lastLevelLoadTime = Globals::MyGetTime();
			m_nextLevelLoadTime = m_lastLevelLoadTime + (5000 * m_currentLevel);
		}
		else
			m_bGameWon = true;			
	}
}

void World::DestroyDeletedObjects()
{
	std::vector<WorldEntity*>::iterator itWorldEntities = m_worldEntities.begin();
	while (itWorldEntities != m_worldEntities.end()) {
		if ((*itWorldEntities)->IsDeleteReady()) {
			delete (*itWorldEntities);
			itWorldEntities = m_worldEntities.erase(itWorldEntities);
		}
		else
			++itWorldEntities;
	}
}

int World::GetScore()
{
	return m_score;
}

void World::SetScore(int _score)
{
	m_score = _score;
}

long long World::GetLastScoreUpdateTime()
{
	return m_lastScoreUpdateTime;
}

void World::SetLastScoreUpdateTime(long long _time)
{
	m_lastScoreUpdateTime = _time;
}

void World::UpdateScore()
{
	Player* player = dynamic_cast<Player*>(m_worldEntities.at(0));

	if (m_lastScoreUpdateTime == 0 || player->IsDead()) {
		m_lastScoreUpdateTime = Globals::MyGetTime();
	}
	else if ((m_lastScoreUpdateTime + 1000 < Globals::MyGetTime()) && !player->IsDead()) {
		m_score += (int)((Globals::MyGetTime() - m_lastScoreUpdateTime) / 1000);
		m_lastScoreUpdateTime = Globals::MyGetTime();
	}
}