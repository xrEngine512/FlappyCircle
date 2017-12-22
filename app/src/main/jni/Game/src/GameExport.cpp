#include "GamePCH.h"
#include "GameExport.h"
#include "Game.h"

Game*				game;

void GameExport::Start()
{
	game = new Game();
}

void GameExport::Stop()
{
	game->Stop();
	delete game;
}

void GameExport::Press()
{
	game->Press();
}

void GameExport::Play()
{
	game->Play();
}

void GameExport::Pause()
{
	game->Pause();
}

void GameExport::Release()
{
	game->Release();
}

void GameExport::Render()
{
	game->Render();
}

bool GameExport::IsOver()
{
    return game->IsOver();
}

