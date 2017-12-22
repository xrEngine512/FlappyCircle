#include "GamePCH.h"
#include "Game.h"
#include "GLESRenderer.h"
#include "Player.h"
#include <chrono>
#include <thread>
#include "Pipe.h"
#include "log.h"

#define LOG_TAG "Game"

Game::Game(): 
	_gameState(GS_Playing),
	_cameraX(),
	_background(.2f, .2f, .2f)
{
	Tools::UpdateScreenResolution();
	_player = new Player();
	_renderer = new GLESRenderer();
	_sceneObjects.push_back(_player);
	_lastTimePoint = std::chrono::high_resolution_clock::now();
}

void Game::Press()
{
	_player->Press();
}

void Game::Release()
{
	_player->Release();
}

void Game::Play()
{
	if (_gameState == GS_Paused)
	{
		_gameState = GS_Playing;
		_lastTimePoint = std::chrono::high_resolution_clock::now();
	}
}

void Game::Pause()
{
	_gameState = GS_Paused;
}

void Game::Stop()
{
	_gameState = GS_Stopped;
}

bool Game::IsOver() const
{
    return _gameState == GS_Over;
}

void Game::Render()
{
	if (_gameState != GS_Stopped)
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = now - _lastTimePoint;
		renderImpl(.001f * elapsed.count());
		_lastTimePoint = now;
	}
}

void Game::renderImpl(float dt)
{
	glClearColor(_background.r, _background.g, _background.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (_gameState == GS_Playing)
	{
		for (auto object : _sceneObjects)
			object->Update(dt);

		doGameLogic(dt);
	}

	for (auto object : _sceneObjects)
		 _renderer->DrawPrimitiveAt(object->Geometry(), object->GetScreenPosition(_cameraPosition));

}

Game::~Game()
{
	delete _renderer;

	for (auto object : _sceneObjects)
		delete object;

	_sceneObjects.clear();
}

void Game::doGameLogic(float dt)
{
	//Player(bird) moves forward every time until death
	Vector2D delta(Constants::ForwardSpeed, 0.f);	//Every second player will be moved on this delta

	_player->Move(delta * dt);

	//Camera is attached to player only in x - direction
	_cameraPosition.x = _player->GetPosition().x;

	//Generate new pipes wile player is moving
	if (_cameraPosition.x > _cameraX)
	{
		_cameraX += Constants::PipesInterval / Tools::GetAspectRatio();
		generateLevelObjects();
	}
	//Stash invisible pipes to reuse

	vector<decltype(_sceneObjects.begin())>	cachedObjects;

	for (auto object = _sceneObjects.begin(); object != _sceneObjects.end();)
	{
		if (auto pipe = dynamic_cast<const Pipe*>(*object))
		{
			if (pipe->GetPosition().x < _cameraPosition.x)
			{
				auto pipeWidth = static_cast<const RectanglePrimitive&>(pipe->Geometry()).GetWidth();
				if (pipe->GetPosition().x + pipeWidth / Tools::GetAspectRatio() < _cameraPosition.x - 1)
				{
					_generator.StashLevelObject(*object);
					cachedObjects.push_back(object);
					object = _sceneObjects.erase(object);
				}
				else
					break;
			}
			else
				break;
		}
		else ++object;
	}


	//Check intersection with...

	//Screen bounds
	auto playerScreenPos = toScreenSpace(_player->GetPosition());
	auto birdRadius = static_cast<const CirclePrimitive&>(_player->Geometry()).GetRadius();
	if (playerScreenPos.y - birdRadius < -1.f || playerScreenPos.y + birdRadius > 1.f) {
        gameOver();
        LOG_INFO("Touched bounds");
    }
	//Pipes
	else
		for (auto object : _sceneObjects)
			if (Tools::Intersects(_player, object))
			{
				gameOver();
                LOG_INFO("Touched pipes");
				break;
			}
}

void Game::generateLevelObjects()
{
	auto objects = _generator.GetLevelObject(_cameraPosition.x + 1);

	_sceneObjects.push_back(objects.first);
	_sceneObjects.push_back(objects.second);
}

void Game::gameOver()
{
	_background = Color(1, 0, 0);
	_gameState = GS_Over;
}

Vector2D Game::toScreenSpace(const Vector2D& point)
{
	return Vector2D(point.x - _cameraPosition.x, point.y - _cameraPosition.y);
}
