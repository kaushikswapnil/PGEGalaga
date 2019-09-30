#include"Bullet.h"
#include"GraphicsManager.h"
#include"ResourceManager.h"
#include"World.h"
#include"Resource_Sprite.h"
#include"Player.h"
#include"Enemy.h"

Bullet::Bullet() : WorldEntity(400.0f, 300.0f, WorldEntityType::WET_BULLET) { }

Bullet::Bullet(float _x, float _y, bool _playerBullet) : WorldEntity(_x, _y, WorldEntityType::WET_BULLET), m_bPlayerBullet(_playerBullet) { }

Bullet::~Bullet() { }

void Bullet::Update(float dt)
{
	if (m_bPlayerBullet)
		m_y -= Globals::BULLET_SPEED;
	else
		m_y += Globals::BULLET_SPEED;

	if (CheckOutOfBounds())
		m_bDelete = true;
	else if (CheckCollision())
		m_bDelete = true;
}

void Bullet::Render()
{
	Resource_Sprite* sprBullet;
	if (m_bPlayerBullet)
		sprBullet = ResourceManager::GetInstance()->RetrieveResourceWrapper("PlayerBulletSprite")->GetResourceContainer<Resource_Sprite>();
	else
		sprBullet = ResourceManager::GetInstance()->RetrieveResourceWrapper("EnemyBulletSprite")->GetResourceContainer<Resource_Sprite>();
	GraphicsManager::GetInstance()->Render(sprBullet, m_x, m_y);
}

bool Bullet::CheckOutOfBounds()
{
	if (m_y < 8)
		return true;
	else if (m_y > 554)
		return true;
	return false;
}

bool Bullet::CheckCollision()
{
	std::vector<WorldEntity*> worldEntities;
	worldEntities = World::GetInstance()->GetWorldEntityVector();
	std::vector<WorldEntity*>::iterator itWorldEntities = worldEntities.begin();
	while (itWorldEntities != worldEntities.end()) {
		if (m_bPlayerBullet)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(*itWorldEntities);
			if (enemy != nullptr) {
				if (!enemy->IsDead()) {
					if (enemy->TestPoint(m_x, m_y)) {
						enemy->SetDead();
						int score = World::GetInstance()->GetScore();
						score += 20;
						World::GetInstance()->SetScore(score);
						return true;
					}
				}
			}
		}
		else {
			Player* player = dynamic_cast<Player*>(*itWorldEntities);
			if (player) {
				if (player->GetPlayerRespawnCoolDownTime() + 2000 < Globals::MyGetTime()) {
					if (player->TestPoint(m_x, m_y)) {
						player->SetDead(true);
						player->PlayDeadAnimation();
						player->SetPlayerRespawnCoolDownTime(Globals::MyGetTime() + 5000);
						player->SetDir(Globals::Direction::STOP);
						return true;
					}
				}
				return false;
			}
		}
		++itWorldEntities;
	}
	return false;
}

