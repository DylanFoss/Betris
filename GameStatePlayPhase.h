#pragma once
#include "GameState.h"
class GameStatePlayPhase :
    public GameState
{
public:
    GameStatePlayPhase();
    GameStatePlayPhase(IStateChanger* manager);
    ~GameStatePlayPhase();

    void OnEnter() override;
    void OnExit() override;
    void Update(const double deltaTime) override;
    void Draw(const double deltaTime) override;

private:

    //pointers to GameData memebers, to help make code more readable.

    //tetromino move/lock
    float stepDelay;
    float lockDelay;
    float stepCounter;
    float lockCounter;
    float wasHardDrop;

    bool gameOver;
    bool tetrominoUpdate;

    //swap/holding
    bool isHoldOnCooldown;

    void MoveTetromino(const double dt);
    void RotateTetromino();
    void SwapTetromino();

    void ApplyOffset(Tetromino& mino);

    int GetNext();

    void UpdateTetrominoes();
    void GenerateTetrominoes();

    void UpdateHUD();
    void InitHUD();

    void CalculateStepDelay();

};

