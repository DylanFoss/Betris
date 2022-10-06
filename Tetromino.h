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

	int x, y;
	int rotation;
	unsigned char tiles[4][4];

	Tetromino();
	Tetromino(const Renderer* renderer, Board* board, int X, int Y, MinoType type);

	void ChangeType(MinoType type);

	void Move(int X, int Y);
	int Rotate(bool lr);

	void Reset();
	void Reset(MinoType type);
	void Reset(MinoType type, int x, int y);

	void Draw();

};

