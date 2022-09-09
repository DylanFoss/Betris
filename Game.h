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

	std::queue<int> tetrominoBucket;
	int bucketCounter;

	//logic
	bool gameOver;
	bool IsMinoHeld;
	float stepCounter;

	bool tetrominoUpdate;

	//line clearing
	std::vector<int> linesToClear;
	float lineClearWait;

public:

	Game(const Renderer* renderer, InputManager* input);

	void UpdateTetrominoes();
	int GetNext();
	void GenerateTetrominoes();

	void MoveTetromino(const double dt);
	void RotateTetromino();

	void Init();
	void Update(const double deltaTime);
	void Draw(const double deltaTime);

	const std::vector<int>& GetLinesToClear() const { return linesToClear; };
};

