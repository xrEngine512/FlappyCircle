#pragma once
#include <queue>

class GameObject;

class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();

	std::pair<GameObject*, GameObject*>	GetLevelObject(float xCoord) const;
	void StashLevelObject(GameObject* object);
private:
	mutable std::queue<GameObject*>		_cache;

	GameObject* getObject() const;
};

