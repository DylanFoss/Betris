#pragma once

#include <array>
#include <vector>
#include <stack>
#include <algorithm>

#include "Renderer.h"
#include "InputManager.h"
#include "GameSettings.h"

#include "Score.h"
#include "ScoreCalculator.h"

#include "Board.h"

#include "Tetromino.h"
#include "ActiveMino.h"
#include "GhostMino.h"
#include "Font.h"

#include "GameStateEnum.h"
#include "GameStateManager.h"
#include "GameStatePlayPhase.h"
#include "GameStateCountdown.h"
#include "GameStateClearLine.h"
#include "GameStatePaused.h"
#include "GameData.h"

class Game
{
private:

	const Renderer* renderer;
	InputManager* input;

	GameSettings settings;
	GameStateEnum state;

	GameData gameData;

	GameStateManager manager;
	GameStateCountdown gs_countdown;
	GameStatePlayPhase gs_playPhase;
	GameStateClearLine gs_clearLine;
	GameStatePaused gs_paused;

	Score scoreTracker;
	ScoreCalculator scoreCalc;

	Board board;

	ActiveMino currentMino;
	GhostMino ghostMino;

	Tetromino heldTetromino;

	Tetromino queue1;
	Tetromino queue2;
	Tetromino queue3;

	Font nextTitle;
	Font scoreTitle;

	Font heldTitle;
	Font score;

	Font linesTitle;
	Font lines;

	Font levelTitle;
	Font level;

	Font paused;
	Font countdown;

	//std::queue<int> tetrominoBucket;

	//logic
	bool gameOver;

	float wasHardDrop;
	bool tetrominoUpdate;

	float stepDelay = 1;
	float stepCounter;

	float lockDelay = 0.5f;
	float lockCounter;

	float countdownCounter = 3;

	//swap/holding
	bool IsMinoHeld;
	bool IsHoldOnCooldown;

	//line clearing
	float lineClearWait;

public:

	Game(const Renderer* renderer, InputManager* input);

	void UpdateTetrominoes();
	int GetNext();
	void GenerateTetrominoes();
	void ApplyOffset(Tetromino& mino);

	void MoveTetromino(const double dt);
	void RotateTetromino();
	void SwapTetromino();

	void CalculateStepDelay();

	void UpdateHUD();
	void InitHUD();

	void Init();
	void Update(const double deltaTime);
	void Draw(const double deltaTime);
};

