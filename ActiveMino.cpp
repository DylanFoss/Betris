#include "ActiveMino.h"

ActiveMino::ActiveMino()
	:Tetromino(), rotatedThisTick(false), numWallKicksThisTick(0)
{
}

ActiveMino::ActiveMino(const Renderer* renderer, Board* board, int X, int Y, MinoType type)
	: Tetromino(renderer,board, X, Y, type), rotatedThisTick(false), numWallKicksThisTick(0)
{
}

bool ActiveMino::CollisionCheck()
{
	return CollisionCheck(x, y);
}

bool ActiveMino::CollisionCheck(int x, int y)
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

bool ActiveMino::Move(int X, int Y)
{
	if (x != 0 || y != 0)
	{
		x += board->cellSize * X;
		y += board->cellSize * Y;

		if (CollisionCheck())
		{
			x -= board->cellSize * X;
			y -= board->cellSize * Y;
			return false;
		}
		else ResetFlags();
	}

	return true;
}

bool ActiveMino::Advance()
{
	return Move(0, -1);
}


int ActiveMino::Rotate(bool lr)
{
	if (type == MinoType::O) return 0;

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

	int numTests = 0;

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

			numTests++;

		}
		else return numTests;

		//test 2

		if (CollisionCheck())
		{
			x = rotX;
			y = rotY;

			if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(1, 0);
			else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(-1, 0);
			else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(2, 0);
			else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(-2, 0);

			numTests++;
		}
		else return numTests;

		//test 3

		if (CollisionCheck())
		{
			x = rotX;
			y = rotY;

			if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(-2, -1);
			else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(2, 1);
			else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(-1, 2);
			else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(1, -2);

			numTests++;
		}
		else return numTests;

		//test 4

		if (CollisionCheck())
		{
			x = rotX;
			y = rotY;

			if ((lastRot == 0 && rotation == 1) || (lastRot == 3 && rotation == 2)) Move(1, 2);
			else if ((lastRot == 1 && rotation == 0) || (lastRot == 2 && rotation == 3)) Move(-1, -2);
			else if ((lastRot == 1 && rotation == 2) || (lastRot == 0 && rotation == 3)) Move(2, -1);
			else if ((lastRot == 2 && rotation == 1) || (lastRot == 3 && rotation == 0)) Move(-2, 1);
			numTests++;
		}
		else return numTests;

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

			numTests++;

		}
		else return numTests;

		//test 2
		if (CollisionCheck())
		{
			x = rotX;
			y = rotY;

			if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1)) Move(-1, 1);
			else if ((lastRot == 1 && rotation == 0) || (lastRot == 1 && rotation == 2)) Move(1, -1);
			else if ((lastRot == 2 && rotation == 3) || (lastRot == 0 && rotation == 3)) Move(1, 1);
			else if ((lastRot == 3 && rotation == 0) || (lastRot == 3 && rotation == 2)) Move(-1, -1);

			numTests++;
		}
		else return numTests;

		//test 3
		if (CollisionCheck())
		{
			x = rotX;
			y = rotY;

			if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1) || (lastRot == 2 && rotation == 3) || (lastRot == 0 && rotation == 3)) Move(0, -2);
			else if ((lastRot == 1 && rotation == 0) || (lastRot == 1 && rotation == 2) || (lastRot == 3 && rotation == 2) || (lastRot == 3 && rotation == 0)) Move(0, 2);

			numTests++;
		}
		else return numTests;

		//test 4
		if (CollisionCheck())
		{
			x = rotX;
			y = rotY;

			if ((lastRot == 0 && rotation == 1) || (lastRot == 2 && rotation == 1)) Move(-1, -2);
			else if ((lastRot == 1 && rotation == 0) || (lastRot == 1 && rotation == 2)) Move(1, 2);
			else if ((lastRot == 2 && rotation == 3) || (lastRot == 0 && rotation == 3)) Move(1, -2);
			else if ((lastRot == 3 && rotation == 2) || (lastRot == 3 && rotation == 0)) Move(-1, 2);

			numTests++;
		}
		else return numTests;

		break;
	}

	if (!CollisionCheck()) return numTests;

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

	// rotations reset
	return -1;
}

void ActiveMino::Lock()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (tiles[i][j] != 0)
				board->grid.at(board->GetGridY(y + i * board->cellSize)).at(board->GetGridX(x + j * board->cellSize)) = tiles[i][j];
}

void ActiveMino::ResetFlags()
{
	rotatedThisTick = 0;
	numWallKicksThisTick = 0;
}
