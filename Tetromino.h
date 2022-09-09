#pragma once
#include <cstring>

#include "Renderer.h"
#include "Board.h"

class Tetromino
{
protected:

	MinoType type;
	Board* board;
	const Renderer* renderer;

public:

	MinoType getType() const { return type; }

	int GetBoardY();

	int x, y;
	int rotation;
	unsigned char tiles[4][4];

	Tetromino();
	Tetromino(const Renderer* renderer, Board* board, int X, int Y, MinoType type);
	Tetromino(const Tetromino& other);
	Tetromino& operator=(const Tetromino& other);

	void ChangeType(MinoType type);

	void Move(int X, int Y);
	void Rotate(bool lr);
	bool CollisionCheck();
	bool CollisionCheck(int x, int y);
	bool Advance();
	void Lock();

	void Reset();
	void Reset(MinoType type);
	void Reset(MinoType type, int x, int y);

	void Draw();

};

