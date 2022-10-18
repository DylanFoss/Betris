#pragma once
#include "GameState.h"
#include "Board.h"
class GameStateClearLine :
    public GameState
{
public:
    GameStateClearLine();
    GameStateClearLine(IStateChanger* manager);
    ~GameStateClearLine();

    void Update(const double dt) override;
    void OnEnter() override;
    void OnExit() override;
    void Draw(const double deltaTime) override;
private:
    float lineClearWait;
    Board* board;
};

