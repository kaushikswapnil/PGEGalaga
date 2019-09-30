#include"Enemy.h"
#include"GraphicsManager.h"
#include"ResourceManager.h"
#include"World.h"
#include"GameManager.h"
#include"AudioManager.h"
#include"Resource_Animation.h"

Enemy::Enemy() : WorldEntity(400.0f, 100.0f, WorldEntityType::WET_ENEMY), m_bDead(false), m_enemyType(BLUE){
	SetRect();
	GetAnimations();
}

Enemy::Enemy(int _type, float _x, float _y) : m_bDead(false), m_enemyType(static_cast<Enemy_Type>(_type)), WorldEntity(_x, _y, WorldEntityType::WET_ENEMY) {
	SetRect();
}

Enemy::Enemy(int _type, Globals::Position _pos) : m_bDead(false), m_enemyType(static_cast<Enemy_Type>(_type)), WorldEntity(_pos.x, _pos.y, WorldEntityType::WET_ENEMY) {
	SetRect();
	GetAnimations();
}

Enemy::~Enemy() {
	delete m_animDeadEnemy;
	delete m_animEnemy;
}

void Enemy::Update(float dt)
{
	UpdateAnimations(dt);
	CanShootBullet();
	SetRect();
}

void Enemy::Render()
{
	if (!m_bDead) {
		GraphicsManager::GetInstance()->Render(m_animEnemy, m_x, m_y);
	}
	else {
		if (m_animDeadEnemy->IsPlaying()) {
			GraphicsManager::GetInstance()->Render(m_animDeadEnemy, m_x, m_y);
		}
		else
			m_bDelete = true;
	}
}

bool Enemy::IsDead() {
	return m_bDead;
}

void Enemy::SetDead() {
	m_bDead = true;
	m_animDeadEnemy->Play();
	Resource_Audio* _resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("Explosion")->GetResourceContainer<Resource_Audio>();
	AudioManager::GetInstance()->PlaySoundEffect(_resAudio);
}

void Enemy::PlayDeadAnim() {
	m_animDeadEnemy->Play();
}

void Enemy::SetRect() {
	m_rect.SetRadius(m_x, m_y, 16);
}

bool Enemy::TestPoint(float _x, float _y) {
	return m_rect.TestPoint(_x, _y);
}

const char* Enemy::GetTypeAnimationName()
{
	switch (m_enemyType) {
	case BLUE:
		return "BlueEnemyAnimation";
		break;
	case GREEN:
		return "GreenEnemyAnimation";
		break;
	case RED:
		return "RedEnemyAnimation";
		break;
	case YELLOW:
		return "YellowEnemyAnimation";
		break;
	default:
		break;
	}
	return "BlueEnemyAnimation";
}

void Enemy::CanShootBullet()
{
	if (m_bDead)
		return;
	int prob = std::rand() % 10000;
	if (prob > (9950 - ((m_enemyType-1)*100))) {
		ShootBullet();
	}
}

void Enemy::ShootBullet()
{
	WorldEntity* we = new Bullet(m_x, m_y + 24, false);
	World::GetInstance()->AddObjectToWorld(we);
}

void Enemy::UpdateAnimations(float dt)
{
	if (!m_bDead)
		m_animEnemy->Update(dt);
	else
		m_animDeadEnemy->Update(dt);
}

void Enemy::GetAnimations()
{
	Resource_Animation* tempAnimEnemy = ResourceManager::GetInstance()->RetrieveResourceWrapper(GetTypeAnimationName())->GetResourceContainer<Resource_Animation>();
	m_animEnemy = new Resource_Animation(*tempAnimEnemy);
	m_animEnemy->Play();
	m_animEnemy->SetLoopMode(true);
	Resource_Animation* tempAnimDeadEnemy = ResourceManager::GetInstance()->RetrieveResourceWrapper("DeadEnemyAnimation")->GetResourceContainer<Resource_Animation>();
	m_animDeadEnemy = new Resource_Animation(*tempAnimDeadEnemy); //Change values here
	m_animDeadEnemy->SetLoopMode(false);
}

