#pragma once
#include "IState.h"
#include "GameStateEnum.h"
#include "GameData.h"
class GameState :
    public IState
{
public:
    GameState();
    GameState(IStateChanger* stateManager);
    GameState(IStateChanger* stateManager, GameData* game);
    ~GameState();
    virtual void Draw(const double deltaTime) = 0;

    void SetStateManager(IStateChanger* manager);
    void SetGame(GameData* gameResources);

protected:
    void ChangeState(int state) override;
    void ChangeState(GameStateEnum state);
    
    GameData* gameData;
};

