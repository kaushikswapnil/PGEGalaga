#include"Resource_LevelPositions.h"

Resource_LevelPositions::Resource_LevelPositions() : Resource()
{
}

Resource_LevelPositions::Resource_LevelPositions(std::vector<std::pair<int, Globals::Position>>* _vecPos) : Resource(), m_resource(_vecPos)
{
}

Resource_LevelPositions::Resource_LevelPositions(const Resource_LevelPositions & _resLevelPos) : Resource()
{
	*m_resource = *_resLevelPos.m_resource;
}

Resource_LevelPositions::~Resource_LevelPositions()
{
	if (m_resource)
	{
		m_resource->clear();
		delete m_resource;
		m_resource = nullptr;
	}
}

std::vector<std::pair<int, Globals::Position>>* Resource_LevelPositions::GetResource()
{
	return m_resource;
}

bool Resource_LevelPositions::LoadResource(std::vector<std::pair<int, Globals::Position>>* _vecPositions)
{
	m_resource = _vecPositions;
	return true;
}
