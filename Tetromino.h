#pragma once
#include <cstring>

#include "Renderer.h"
#include "Board.h"

enum class Type
{
	I,
	L,
	J,
	O,
	S,
	Z,
	T
};

class Tetromino
{
protected:

	Type type;
	Board* board;
	const Renderer* renderer;

public:

	Type getType() const { return type; }

	int GetBoardY();

	int x, y;
	int rotation;
	unsigned char tiles[4][4];

	Tetromino();
	Tetromino(const Renderer* renderer, Board* board, int X, int Y, Type type);
	Tetromino(const Tetromino& other);
	Tetromino& operator=(const Tetromino& other);

	void ChangeType(Type type);

	void Move(int X, int Y);
	void Rotate(bool lr);
	bool CollisionCheck();
	bool CollisionCheck(int x, int y);
	bool Advance();
	void Lock();

	void Reset();
	void Reset(Type type);
	void Reset(Type type, int x, int y);

	void Draw();

};

