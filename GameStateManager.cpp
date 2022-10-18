#include "GameStateManager.h"

GameStateManager::GameStateManager()
	:currentIndex(-1)
{
	gameData = nullptr;
}

GameStateManager::GameStateManager(GameData* gameData)
	: currentIndex(-1), gameData(gameData)
{
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::ChangeState(GameStateEnum newState)
{
	ChangeState(static_cast<int>(newState));
}

void GameStateManager::ChangeState(int newstate)
{
	if (currentIndex != -1)
		states.at(currentIndex)->OnExit();
	currentIndex = newstate;
	states.at(currentIndex)->OnEnter();
}

void GameStateManager::AddState(GameState* gamestate)
{
	gamestate->SetStateManager(this);
	gamestate->SetGame(gameData);
	states.emplace_back(gamestate);
}

GameState* GameStateManager::GetCurrentState()
{
	return states.at(currentIndex);
}
