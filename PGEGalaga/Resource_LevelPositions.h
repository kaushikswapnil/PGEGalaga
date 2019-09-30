#pragma once
#include"Resource.h"

class Resource_LevelPositions : public Resource
{
public:
	Resource_LevelPositions();
	Resource_LevelPositions(std::vector<std::pair<int, Globals::Position>>* _vecPos);
	Resource_LevelPositions(const Resource_LevelPositions& _resLevelPos);

	~Resource_LevelPositions();

	std::vector<std::pair<int, Globals::Position>>* GetResource();

	bool LoadResource(std::vector<std::pair<int, Globals::Position>>* _vecPositions);

private:
	std::vector<std::pair<int, Globals::Position>>* m_resource{};
};

