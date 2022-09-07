#pragma once

#include <array>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>

#include "Renderer.h"
#include "InputManager.h"

#include "Board.h"
#include "Tetromino.h"
#include "GhostPiece.h"

class Game
{
private:

	const Renderer* renderer;
	InputManager* input;

	Board board;
	Tetromino currentTetromino;
	GhostPiece ghostPiece;

	Tetromino heldTetromino;

	Tetromino queue1;
	Tetromino queue2;
	Tetromino queue3;

	std::stack<int> tetrominoBucket;
	int bucketCounter;

	//logic
	bool gameOver;

	float logicCounter;
	float lastPressed;

public:

	Game(const Renderer* renderer, InputManager* input);

	void UpdateTetrominoes();
	int GetNext();
	void GenerateTetrominoes();

	void MoveTetromino(const double dt);
	void RotateTetromino();

	void Init();
	void Update(const double deltaTime);
	void Draw();
};

