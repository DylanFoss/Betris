#pragma once
#include "IStateManager.h"
#include "GameState.h"
#include <vector> 
class GameStateManager :
    public IStateManager
{
public:
    GameStateManager();
    GameStateManager(GameData* gameData);
    ~GameStateManager();

    void ChangeState(GameStateEnum state);
    void ChangeState(int newstate);
    void AddState(GameState* gamestate);

    GameState* GetCurrentState();

private:
    std::vector<GameState*> states;
    int currentIndex;
    GameData* gameData;
};

