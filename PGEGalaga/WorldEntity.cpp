#include "WorldEntity.h"

WorldEntity::WorldEntity(float _x, float _y, WorldEntityType _entityType) : m_x(_x), m_y(_y), m_entityType(_entityType)
{
}

WorldEntity::~WorldEntity()
{
}

bool WorldEntity::IsDeleteReady()
{
	return m_bDelete;
}

void WorldEntity::SetDelete(bool _delete)
{
	m_bDelete = _delete;
}

float WorldEntity::GetX()
{
	return m_x;
}

float WorldEntity::GetY()
{
	return m_y;
}

void WorldEntity::SetX(float _x)
{
	m_x = _x;
}

void WorldEntity::SetY(float _y)
{
	m_y = _y;
}
