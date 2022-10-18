#pragma once
#include "GameState.h"
#include "Font.h"
class GameStateCountdown :
    public GameState
{
public:
    GameStateCountdown();
    GameStateCountdown(IStateChanger* manager);
    ~GameStateCountdown();

    void OnEnter() override;
    void OnExit() override;
    void Update(const double deltaTime) override;
    void Draw(const double deltaTime) override;

private:
    float countdownCounter;
};

