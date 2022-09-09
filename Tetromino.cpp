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

Tetromino::Tetromino(const Tetromino& other)
	: renderer(other.renderer), board(other.board), x(other.x), y(other.y), type(other.type), rotation(other.rotation)
{
	std::memcpy(tiles, other.tiles, 4 * 4 * sizeof(unsigned char));
}

Tetromino& Tetromino::operator=(const Tetromino& other)
{
	if (&other != this)
	{
		type = other.type;
		board = other.board;
		renderer = other.renderer;

		x = other.x;
		y = other.y;
		rotation = other.rotation;
		std::memcpy(tiles, other.tiles, 4 * 4 * sizeof(unsigned char));
	}
	return *this;
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

bool Tetromino::CollisionCheck()
{
	return CollisionCheck(x, y);
}

bool Tetromino::CollisionCheck(int x, int y)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (tiles[i][j] != 0)
			{
				//OOB checks with grid

				if ((x + j * board->cellSize) < board->x || (x + j * board->cellSize) > board->x + board->boardWidth * board->cellSize - 1)
					return true;


				if ((y + i * board->cellSize) < board->y || (y + i * board->cellSize) > board->y + board->boardHeight * board->cellSize - 1)
					return true;

				// checks with other blocks

				if (board->grid.at(board->GetGridY(y + i * board->cellSize)).at(board->GetGridX(x + j * board->cellSize)) != 0)
					return true;
			}
		}

	return false;
}

void Tetromino::Move(int X, int Y)
{
	x +=  board->cellSize * X;
	y +=  board->cellSize * Y;
}

void Tetromino::Rotate(bool lr)
{
	if (type == MinoType::O) return;

	unsigned char ret[4][4] = { 0 };

	unsigned char initial[4][4]; // for returning if all rotations fail, could be optimised for compeletly irrelavant memory savings.
	unsigned int initialX = x;
	unsigned int initialY = y;
	int rotX;
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

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			initial[i][j] = tiles[i][j];
			tiles[i][j] = ret[i][j];
		}
	}

	if (rotation < 0) rotation = 3;
	if (rotation > 3) rotation = 0;

	switch (type)
	{
		case MinoType::I:

			//no offsets for basic rotation...

			rotX = x;
			rotY = y;

			//wall kicks

			//test 1

			if (CollisionCheck())
			{

				if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(-2, 0);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(2, 0);
				else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(-1, 0);
				else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(1, 0);

				std::cout << "Test 1" << '\n';

			}
			else return;

			//test 2

			if (CollisionCheck())
			{
				x = rotX;
				y = rotY;

				if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(1, 0);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(-1, 0);
				else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(2, 0);
				else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(-2, 0);

				std::cout << "Test 2" << '\n';
			}
			else return;

			//test 3

			if (CollisionCheck())
			{
				x = rotX;
				y = rotY;

				if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(-2, -1);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(2, 1);
				else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(-1, 2);
				else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(1, -2);

				std::cout << "Test 3" << '\n';
			}
			else return;

			//test 4

			if (CollisionCheck())
			{
				x = rotX;
				y = rotY;

				if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(1, 2);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(-1, -2);
				else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(2, -1);
				else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(-2, 1);
				std::cout << "Test 4" << '\n';
			}
			else return;

			break;
		case MinoType::L:
		case MinoType::J:
		case MinoType::S:
		case MinoType::Z:
		case MinoType::T:

			// initial rotation
			if (!lr)
			{
				if ((lastRot == 0 && rotation == 1)) Move(0, -1);
				else if (lastRot == 1 && rotation == 2) Move(-1, 0);
				else if (lastRot == 2 && rotation == 3) Move(0, +1);
				else if (lastRot == 3 && rotation == 0) Move(+1, 0);
			}
			else {
				if ((lastRot == 0 && rotation == 3)) Move(-1, 0);
				else if (lastRot == 3 && rotation == 2) Move(0, -1);
				else if (lastRot == 2 && rotation == 1) Move(+1, 0);
				else if (lastRot == 1 && rotation == 0) Move(0, +1);
			}

			rotX = x;
			rotY = y;

			// wall kicks

			//test 1
			if (CollisionCheck())
			{

				if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 2) || (lastRot == 3 && rotation == 0)) Move(-1, 0);
				else Move(1, 0);

				std::cout << "Test 1" << '\n';

			}
			else return;

			//test 2
			if (CollisionCheck())
			{
				x = rotX;
				y = rotY;

				if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1)) Move(-1, 1);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 1 && rotation == 2)) Move(1, -1);
				else if ((lastRot == 2 && rotation == 3) || (lastRot == 0 && rotation == 3)) Move(1, 1);
				else if ((lastRot == 3 && rotation == 0) || (lastRot == 3 && rotation == 2)) Move(-1, -1);

				std::cout << "Test 2" << '\n';
			}
			else return;

			//test 3
			if (CollisionCheck())
			{
				x = rotX;
				y = rotY;

				if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1) || (lastRot == 2 && rotation == 3) || (lastRot == 0 && rotation == 3)) Move(0, -2);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 1 && rotation == 2) || (lastRot == 3 && rotation == 2) || (lastRot == 3 && rotation == 0)) Move(0, 2);

				std::cout << "Test 3" << '\n';
			}
			else return;

			//test 4
			if (CollisionCheck())
			{
				x = rotX;
				y = rotY;

				if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1)) Move(-1, -2);
				else if ((lastRot == 1 && rotation == 0) || (lastRot == 1 && rotation == 2)) Move(1, 2);
				else if ((lastRot == 2 && rotation == 3) || (lastRot == 0 && rotation == 3)) Move(1, -2);
				else if ((lastRot == 3 && rotation == 2) || (lastRot == 3 && rotation == 0)) Move(-1, 2);

				std::cout << "Test 4" << '\n';
			}
			else return;

			break;
	}

	if (!CollisionCheck()) return;

	// all checks have failed, rotate back.

	x = initialX;
	y = initialY;

	rotation--;
	if (rotation < 0) rotation = 3;
	if (rotation > 3) rotation = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tiles[i][j] = initial[i][j];
		}
	}


	//// basic rotation checks
	//while (WallCollision())
	//{
	//	if (x < board.x)
	//		x += board.cellSize;
	//	else
	//		x -= board.cellSize;
	//}
}

bool Tetromino::Advance()
{
	y -= board->cellSize;

	if (CollisionCheck())
	{
		y += board->cellSize;
		return false;
	}

	return true;
}

void Tetromino::Lock()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (tiles[i][j] != 0) 
				board->grid.at(board->GetGridY(y + i * board->cellSize)).at(board->GetGridX(x + j * board->cellSize)) = tiles[i][j];
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

//// returns the Y relative to the gird based on the first non-0 value in the tiles matrix. Used for line detection.
//int Tetromino::GetBoardY()
//{
//	if (board == nullptr)
//	{
//		std::cout << "No board assigned to tetromino, cannot retrive board Y" << '\n';
//		return 0;
//	}
//
//	for (int Y = 0; Y < 4; Y++)
//		for (int X = 0; X < 4; X++)
//			if (tiles[Y][X] != 0)
//				return board->GetGridY(y + Y);
//
//	return 0;
//}

void Tetromino::Draw()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (tiles[i][j] == 0) {}
			else renderer->drawMino(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), static_cast<MinoType>(tiles[i][j] - 1), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
		}
}

