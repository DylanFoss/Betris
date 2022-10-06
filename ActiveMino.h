#pragma once
#include "Tetromino.h"
class ActiveMino : public Tetromino
{
public:

	ActiveMino();
	ActiveMino(const Renderer* renderer, Board* board, int X, int Y, MinoType type);

	void Move(int X, int Y);
	int Rotate(bool lr);
	bool CollisionCheck();
	bool CollisionCheck(int x, int y);
	bool Advance();
	void Lock();
};

