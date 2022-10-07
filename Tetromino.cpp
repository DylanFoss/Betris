#include "Tetromino.h"
#include <iostream>

Tetromino::Tetromino()
	: renderer(nullptr), board(nullptr), x(0), y(0), type(MinoType::I), rotation(0)
{
	ChangeType(type);
}

Tetromino::Tetromino(const Renderer* renderer, Board* board, int X = 0, int Y = 0, MinoType type = MinoType::I)
	: renderer(renderer), board(board), x(X), y(Y), type(type), rotation(0)
{
	ChangeType(type);
}

void Tetromino::ChangeType(MinoType type)
{
	std::memset(tiles, 0, sizeof(tiles));

	switch (type)
	{
	case MinoType::I:

		tiles[2][0] = 1;
		tiles[2][1] = 1;
		tiles[2][2] = 1;
		tiles[2][3] = 1;

		break;
	case MinoType::L:

		tiles[1][0] = 2;
		tiles[1][1] = 2;
		tiles[1][2] = 2;
		tiles[2][2] = 2;

		break;
	case MinoType::J:

		tiles[1][0] = 3;
		tiles[1][1] = 3;
		tiles[1][2] = 3;
		tiles[2][0] = 3;
		break;
	case MinoType::O:

		tiles[1][2] = 4;
		tiles[1][1] = 4;
		tiles[2][2] = 4;
		tiles[2][1] = 4;
		break;
	case MinoType::S:
		tiles[2][1] = 5;
		tiles[2][2] = 5;
		tiles[1][0] = 5;
		tiles[1][1] = 5;
		break;
	case MinoType::Z:
		tiles[2][0] = 6;
		tiles[2][1] = 6;
		tiles[1][1] = 6;
		tiles[1][2] = 6;
		break;
	case MinoType::T:

		tiles[1][0] = 7;
		tiles[1][1] = 7;
		tiles[1][2] = 7;
		tiles[2][1] = 7;

		break;
	}
}

void Tetromino::Offset(int X, int Y)
{
	x +=  board->cellSize * X;
	y +=  board->cellSize * Y;
}

void Tetromino::Rotate(bool lr)
{
	if (type == MinoType::O);

	unsigned char ret[4][4] = { 0 };
	int rotY;
	
	int lastRot = rotation;
	if (lr) rotation--;
	else rotation++;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (rotation < lastRot) ret[i][j] = tiles[4 - j - 1][i]; 
			if (rotation > lastRot) ret[i][j] = tiles[j][4 - i - 1];
		}

	if (rotation < 0) rotation = 3;
	if (rotation > 3) rotation = 0;


	switch (type)
	{
		case MinoType::I:

			//no offsets for basic rotation...

			break;
		case MinoType::L:
		case MinoType::J:
		case MinoType::S:
		case MinoType::Z:
		case MinoType::T:

			if (!lr)
			{
				if ((lastRot == 0 && rotation == 1)) Offset(0, -1);
				else if (lastRot == 1 && rotation == 2) Offset(-1, 0);
				else if (lastRot == 2 && rotation == 3) Offset(0, +1);
				else if (lastRot == 3 && rotation == 0) Offset(+1, 0);
			}
			else {
				if ((lastRot == 0 && rotation == 3)) Offset(-1, 0);
				else if (lastRot == 3 && rotation == 2) Offset(0, -1);
				else if (lastRot == 2 && rotation == 1) Offset(+1, 0);
				else if (lastRot == 1 && rotation == 0) Offset(0, +1);
			}

		break;
	}
}

void Tetromino::Reset()
{
	Reset(type, x, y);
}

void Tetromino::Reset(MinoType newType)
{
	Reset(newType, x, y);
}

void Tetromino::Reset(MinoType type, int x, int y)
{
	this->type = type;
	rotation = 0;

	ChangeType(type);

	this->x = x;
	this->y = y;
}

void Tetromino::Draw()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (tiles[i][j] == 0) {}
			else renderer->drawMino(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), static_cast<MinoType>(tiles[i][j] - 1), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
		}

	//int xOffset = 0;
	//int yOffset = 0;

	//switch (rotation)
	//{
	//case 0:
	//	break;
	//case 1:
	//	yOffset = 1;
	//	break;
	//case 2:
	//	xOffset = 1;
	//	yOffset = 1;
	//	break;
	//case 3:
	//	xOffset = 1;
	//	break;
	//}

	//if (type == MinoType::T)
	//{
	//	renderer->drawMino(board->cellSize, x + xOffset * 7, y + yOffset * 7, static_cast<MinoType>(5), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
	//	renderer->drawMino(board->cellSize, x + 2*7 + xOffset * 7, y + yOffset * 7, static_cast<MinoType>(5), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
	//	renderer->drawMino(board->cellSize, x + xOffset * 7, y + 2*7 + yOffset * 7, static_cast<MinoType>(5), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
	//	renderer->drawMino(board->cellSize, x + 2*7 + xOffset * 7, y + 2*7 + yOffset * 7, static_cast<MinoType>(5), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
	//}
}

