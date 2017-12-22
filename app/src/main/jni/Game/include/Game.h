#pragma once
#include "DataTypes.h"
#include "Enums.h"
#include "LevelGenerator.h"
#include <atomic>

class GameObject;
class Player;
class GLESRenderer;

class Game
{
public:
	Game();
	void Press();
	void Release();
	void Play();
	void Pause();
	void Stop();
	void Render();
    bool IsOver() const;
	~Game();
private:
	std::atomic<GameState>		_gameState;
	GLESRenderer*				_renderer;
	Player*						_player;
	vector<GameObject*>			_sceneObjects;
	Vector2D					_cameraPosition;
	LevelGenerator				_generator;
	float						_cameraX;
	Color						_background;
	TimePoint					_lastTimePoint;

	void renderImpl(float dt);
	void doGameLogic(float dt);
	void generateLevelObjects();
	void gameOver();

	Vector2D toScreenSpace(const Vector2D& point);
};

