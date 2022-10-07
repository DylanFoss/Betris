#pragma once
#include "Tetromino.h"
class ActiveMino : public Tetromino
{

private:
	bool rotatedThisTick;
	int	numWallKicksThisTick;

public:

	ActiveMino();
	ActiveMino(const Renderer* renderer, Board* board, int X, int Y, MinoType type);

	bool Move(int X, int Y);
	int Rotate(bool lr);
	bool CollisionCheck();
	bool CollisionCheck(int x, int y=0);
	bool Advance();
	void Lock();

	void Reset();
	void Reset(MinoType type);
	void Reset(MinoType type, int x, int y);

	void ResetFlags();
};

