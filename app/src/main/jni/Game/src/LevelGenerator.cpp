#include "GamePCH.h"
#include "LevelGenerator.h"
#include "Pipe.h"
#include <assert.h>
#include <ctime>

LevelGenerator::LevelGenerator()
{
	srand(time(NULL));
}


LevelGenerator::~LevelGenerator()
{
	while(!_cache.empty())
	{
		delete _cache.front();
		_cache.pop();
	}
}

float getRandNumber(float from, float to)
{
	assert(from < to);
	
	auto max = int(10000 * (to - from));
	auto number = rand() % max;

	return .0001f * number + from;
}

std::pair<GameObject*, GameObject*> LevelGenerator::GetLevelObject(float xCoord) const
{
	auto object1 = getObject();
	auto object2 = getObject();

	if(auto upperPipe = dynamic_cast<Pipe*>(object1))
	if(auto downPipe = dynamic_cast<Pipe*>(object2))
	{
		auto upperPipeHeight = getRandNumber(.4f, 1.4f);

		upperPipe->SetPosition(Vector2D(xCoord, 1.f));
		static_cast<RectanglePrimitive&>(upperPipe->Geometry()).SetHeight(upperPipeHeight);

		auto downPipeY = 1.f - upperPipeHeight - Constants::WindowBetweenPipesSize;

		downPipe->SetPosition(Vector2D(xCoord, downPipeY));
		static_cast<RectanglePrimitive&>(downPipe->Geometry()).SetHeight(1.f + downPipeY);
	}	

	return std::make_pair(object1, object2);
}

void LevelGenerator::StashLevelObject(GameObject* object)
{
	_cache.push(object);
}

GameObject* LevelGenerator::getObject() const
{
	if (_cache.empty())
		return new Pipe();

	auto object = _cache.front();
	_cache.pop();
	return object;
}
