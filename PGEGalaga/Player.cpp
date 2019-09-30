#include"Player.h"
#include"GameManager.h"
#include"ResourceManager.h"
#include"GraphicsManager.h"
#include"AudioManager.h"
#include"InputManager.h"
#include"Bullet.h"
#include"World.h"
#include"Resource_Audio.h"
#include"Resource_Sprite.h"
#include"Resource_Animation.h"

Player::Player() : WorldEntity(400.0f, 550.0f, WorldEntityType::WET_PLAYER), m_dir(Globals::Direction::STOP) {
	m_rect.SetRadius(m_x, m_y, 16);
	GetRenderObjects();
	InputManager::GetInstance()->AddSubscriber(this);
}

Player::Player(Globals::Position _pos) : WorldEntity(_pos.x, _pos.y, WorldEntityType::WET_PLAYER), m_dir(Globals::Direction::STOP)
{
	m_rect.SetRadius(m_x, m_y, 16);
	GetRenderObjects();
	InputManager::GetInstance()->AddSubscriber(this);
}

Player::~Player() {
	InputManager::GetInstance()->RemoveSubscriber(this);
}

void Player::SetDir(Globals::Direction _dir) {
	m_dir = _dir;
}

Globals::Direction Player::GetDir() {
	return m_dir;
}

void Player::Update(float dt)
{
	if (GetDir() == Globals::Direction::LEFT)
		MoveLeft();
	else if (GetDir() == Globals::Direction::RIGHT)
		MoveRight();
	if (m_bPlayerDead) {
		m_animDeadPlayer->Update(dt);
		RespawnPlayer();
	}
}

void Player::Render()
{
	if (!m_bPlayerDead)
		GraphicsManager::GetInstance()->Render(m_sprPlayer, m_x, m_y);
	else if (m_bPlayerDead && m_animDeadPlayer->IsPlaying())
		GraphicsManager::GetInstance()->Render(m_animDeadPlayer, m_x, m_y);
}


//Special Functions


void Player::Reset() {
	m_playerSpeed = Globals::BASE_PLAYER_SPEED;
	m_lastPlayerBulletShootTime = 0;
	m_playerRespawnCoolDownTime = 0;
	m_bPlayerDead = false;
	m_x = 400.0f;
}

bool Player::IsDead() {
	return m_bPlayerDead;
}

void Player::SetDead(bool _bPlayerDead) {
	int health = World::GetInstance()->GetPlayerHealth();
	--health;
	World::GetInstance()->SetPlayerHealth(health);
	m_bPlayerDead = _bPlayerDead;
	m_animDeadPlayer->Play();
	Resource_Audio* resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("Explosion")->GetResourceContainer<Resource_Audio>();
	AudioManager::GetInstance()->PlaySoundEffect(resAudio);
}

float Player::GetPlayerSpeed()
{
	return m_playerSpeed;
}

void Player::SetPlayerSpeed(float _speed)
{
	m_playerSpeed = _speed;
}

long long Player::GetLastPlayerBulletShootTime()
{
	return m_lastPlayerBulletShootTime;
}

void Player::SetLastPlayerBulletShootTime(long long _time)
{
	m_lastPlayerBulletShootTime = _time;
}

long long Player::GetPlayerRespawnCoolDownTime()
{
	return m_playerRespawnCoolDownTime;
}

void Player::SetPlayerRespawnCoolDownTime(long long _time)
{
	m_playerRespawnCoolDownTime = _time;
}

void Player::MoveRight()
{
	if (m_dir == Globals::Direction::RIGHT) {
		m_playerSpeed += 0.2f;
		if (m_playerSpeed > Globals::MAX_PLAYER_SPEED)
			m_playerSpeed -= 0.2f;

		m_x += m_playerSpeed;

		if (m_x > 784) {
			m_x = 784 - (m_x - 784);
			Resource_Audio* resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("MenuSND")->GetResourceContainer<Resource_Audio>();
			AudioManager::GetInstance()->PlaySoundEffect(resAudio);
		}
	}
	m_rect.SetRadius(m_x, m_y, 16);
}

void Player::MoveLeft()
{
	if (m_dir == Globals::Direction::LEFT) {
		m_playerSpeed += 0.2f;
		if (m_playerSpeed > Globals::MAX_PLAYER_SPEED)
			m_playerSpeed -= 0.2f;

		m_x -= m_playerSpeed;

		if (m_x < 16) {
			m_x = 16 + (16 - m_x);
			Resource_Audio* resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("MenuSND")->GetResourceContainer<Resource_Audio>();
			AudioManager::GetInstance()->PlaySoundEffect(resAudio);
		}
	}
	m_rect.SetRadius(m_x, m_y, 16);
}

void Player::RespawnPlayer()
{
	if (m_playerRespawnCoolDownTime < Globals::MyGetTime()) {
		m_bPlayerDead = false;
		m_x = 400.0f;
	}
}

void Player::CanShootBullet()
{
	if (m_lastPlayerBulletShootTime == 0) {
		m_lastPlayerBulletShootTime = Globals::MyGetTime();
		WorldEntity* we = new Bullet(m_x, m_y - 24, true);
		World::GetInstance()->AddObjectToWorld(we);
		Resource_Audio* resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("BulletSND")->GetResourceContainer<Resource_Audio>();
		AudioManager::GetInstance()->PlaySoundEffect(resAudio);
	}
	else if (m_lastPlayerBulletShootTime + 500 < Globals::MyGetTime()) {
		WorldEntity* we = new Bullet(m_x, m_y - 24, true);
		World::GetInstance()->AddObjectToWorld(we);
		m_lastPlayerBulletShootTime = Globals::MyGetTime();
		Resource_Audio* resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("BulletSND")->GetResourceContainer<Resource_Audio>();
		AudioManager::GetInstance()->PlaySoundEffect(resAudio);
	}
}

void Player::ShootBullet()
{
	WorldEntity* we = new Bullet(m_x, m_y - 24, true);
	World::GetInstance()->AddObjectToWorld(we);
	Resource_Audio* resAudio = ResourceManager::GetInstance()->RetrieveResourceWrapper("BulletSND")->GetResourceContainer<Resource_Audio>();
	AudioManager::GetInstance()->PlaySoundEffect(resAudio);
}

bool Player::TestPoint(float _x, float _y)
{
	return m_rect.TestPoint(_x, _y);
}

void Player::PlayDeadAnimation()
{
	m_animDeadPlayer->Play();
}

void Player::GetRenderObjects()
{
	m_sprPlayer = ResourceManager::GetInstance()->RetrieveResourceWrapper("PlayerSprite")->GetResourceContainer<Resource_Sprite>();
	m_animDeadPlayer = ResourceManager::GetInstance()->RetrieveResourceWrapper("PlayerDeadAnimation")->GetResourceContainer<Resource_Animation>();
	m_animDeadPlayer->SetLoopMode(false);
}

void Player::ListenToEvent(Event * _event)
{
	Input_KeyEvent* keyEvent = dynamic_cast<Input_KeyEvent*>(_event);
	if (keyEvent)
		HandleInput(keyEvent);
}

void Player::HandleInput(Input_KeyEvent* _keyEvent)
{
	if (((_keyEvent->GetVirtualKey() == PGEK_LEFTARROW && _keyEvent->IsDown() == false) || (_keyEvent->GetVirtualKey() == PGEK_RIGHTARROW && _keyEvent->IsDown() == false)) && !IsDead()) {
		SetPlayerSpeed(Globals::BASE_PLAYER_SPEED);
		SetDir(Globals::Direction::STOP);
	}

	else if (!IsDead() && _keyEvent->IsDown() == true) {

		switch (_keyEvent->GetVirtualKey()) {
		case PGEK_SPACE:
			CanShootBullet();
			break;
		case PGEK_LEFTARROW:
			SetDir(Globals::Direction::LEFT);
			break;
		case PGEK_RIGHTARROW:
			SetDir(Globals::Direction::RIGHT);
			break;
		default:
			break;

		}

	}
}
