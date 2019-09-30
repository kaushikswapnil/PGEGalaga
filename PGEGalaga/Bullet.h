#pragma once
#include"WorldEntity.h"

class Bullet : public WorldEntity {

private:
	bool m_bPlayerBullet;

public:
	Bullet();
	Bullet(float _x, float _y, bool _playerBullet);
	~Bullet();

	void Update(float dt);
	void Render();

	bool CheckOutOfBounds();
	bool CheckCollision();

};
