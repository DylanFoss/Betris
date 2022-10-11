#pragma once

#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>

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

enum class GameState
{
	PLAYPHASE,
	CLEARLINE
};

class Game
{
private:

	const Renderer* renderer;
	InputManager* input;

	GameSettings settings;
	GameState state;

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

	std::queue<int> tetrominoBucket;
	int bucketCounter;

	//logic
	bool gameOver;

	float wasHardDrop;
	bool tetrominoUpdate;

	float stepDelay = 1;
	float stepCounter;
	void CalculateStepDelay();

	float lockDelay = 0.5f;
	float lockCounter;

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

	void UpdateHUD();

	void Init();
	void Update(const double deltaTime);
	void Draw(const double deltaTime);
};

