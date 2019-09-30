#pragma once

#include"Subscriber.h"
#include"Input_KeyEvent.h"
#include"WorldEntity.h"

class Resource_Sprite;
class Resource_Animation;

class Player : public WorldEntity, public Subscriber {
private:
	Globals::Direction m_dir;
	bool m_bPlayerDead{ false };
	float m_playerSpeed{ Globals::BASE_PLAYER_SPEED };
	long long m_lastPlayerBulletShootTime{ 0 };
	long long m_playerRespawnCoolDownTime{ 0 };

	Resource_Sprite* m_sprPlayer{ nullptr };
	Resource_Animation* m_animDeadPlayer{ nullptr };
	//int power; to be implemented later

public:
	Player();
	Player(Globals::Position _pos);
	~Player();
	
	void SetDir(Globals::Direction _dir);

	Globals::Direction GetDir();

	void Update(float dt);
	void Render();

	//Special Functions
	void Reset();
	//void SetPowerUp(); to be implemented later

	bool IsDead();
	void SetDead(bool _bPlayerDead);
	void SetHealth(int _health);
	int GetHealth();

	float GetPlayerSpeed();
	void SetPlayerSpeed(float _speed);

	long long GetLastPlayerBulletShootTime();
	void SetLastPlayerBulletShootTime(long long _time);

	long long GetPlayerRespawnCoolDownTime();
	void SetPlayerRespawnCoolDownTime(long long _time);

	void MoveRight();
	void MoveLeft();
	void RespawnPlayer();

	void CanShootBullet();
	void ShootBullet();
	bool TestPoint(float _x, float _y);

	void PlayDeadAnimation();

	void GetRenderObjects();

	void ListenToEvent(Event* _event);
	void HandleInput(Input_KeyEvent* _keyEvent);
};