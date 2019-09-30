#pragma once
#include"WorldEntity.h"
#include"Bullet.h"

class Resource_Animation;

enum Enemy_Type {BLUE = 1, GREEN, RED, YELLOW};

class Enemy : public WorldEntity {
private:
	bool m_bDead;
	Resource_Animation* m_animDeadEnemy{ nullptr };
	Resource_Animation* m_animEnemy{ nullptr };
	Enemy_Type m_enemyType;

	std::string m_animName;

public:
	Enemy();
	Enemy(int _type, float _x, float _y);
	Enemy(int _type, Globals::Position _pos);
	~Enemy();

	virtual void Update(float dt) override;
	virtual void Render() override;

	bool IsDead();
	void SetDead();

	//Animation functions
	void PlayDeadAnim();

	//Rectangle Functions
	void SetRect();
	bool TestPoint(float _x, float _y);

	const char* GetTypeAnimationName();

	void CanShootBullet();
	void ShootBullet();
	void UpdateAnimations(float dt);

	void GetAnimations();
};