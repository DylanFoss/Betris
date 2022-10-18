#include "GameState.h"

GameState::GameState()
	: IState(), gameData(nullptr)
{
}

GameState::GameState(IStateChanger* stateManager)
	:IState(stateManager), gameData(nullptr)
{
}

GameState::GameState(IStateChanger* stateManager, GameData* game)
	: IState(stateManager), gameData(game)
{
}

GameState::~GameState()
{
}

void GameState::SetStateManager(IStateChanger* newManager)
{
	manager = newManager;
}

void GameState::SetGame(GameData* gameResources)
{
	gameData = gameResources;
}

void GameState::ChangeState(int state)
{
	manager->ChangeState(state);
}

void GameState::ChangeState(GameStateEnum state)
{
	manager->ChangeState(static_cast<int>(state));
}
