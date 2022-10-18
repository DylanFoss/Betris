#pragma once
#include "GameState.h"
class GameStatePaused :
    public GameState
{
public:
    void Update(const double dt) override;
    void OnEnter() override;
    void OnExit() override;
    void Draw(const double deltaTime) override;
};

