#pragma once

#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>

#include "Renderer.h"
#include "InputManager.h"

#include "Board.h"
#include "Tetromino.h"
#include "GhostPiece.h"
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

	GameState state;

	Board board;
	Tetromino currentTetromino;
	GhostPiece ghostPiece;

	Tetromino heldTetromino;

	Tetromino queue1;
	Tetromino queue2;
	Tetromino queue3;

	Font Next;
	Font Score;
	Font Held;

	std::queue<int> tetrominoBucket;
	int bucketCounter;

	//logic
	bool gameOver;

	float stepCounter;
	bool tetrominoUpdate;

	//swap/holding
	bool IsMinoHeld;
	bool IsHoldOnCooldown;

	//line clearing
	std::vector<int> linesToClear;
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

	void Init();
	void Update(const double deltaTime);
	void Draw(const double deltaTime);

	const std::vector<int>& GetLinesToClear() const { return linesToClear; };
};

