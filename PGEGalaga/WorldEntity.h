#pragma once

#include <puruRect.h>

enum WorldEntityType {
	WET_PLAYER = 0,
	WET_ENEMY = 1,
	WET_BULLET = 2
};

class WorldEntity {
protected:
	float m_x, m_y;
	bool m_bDelete{ false };
	WorldEntityType m_entityType;
	puruRect m_rect;

public:
	WorldEntity(float _x, float _y, WorldEntityType _entityType);
	virtual ~WorldEntity();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	bool IsDeleteReady();
	void SetDelete(bool _delete);

	float GetX();
	float GetY();

	void SetX(float _x);
	void SetY(float _y);
};