#include "Game.h"

#define BW			12
#define BH			18
#define	cellSize	7

Game::Game(const Renderer* renderer, InputManager* input)
	:renderer(renderer), input(input)
{
	board = Board(renderer, BW, BH, cellSize, 0+cellSize, 0+cellSize);
	currentTetromino = Tetromino(renderer, &board, 5 * cellSize + cellSize, 14 * cellSize + cellSize, Type::I);
	queue1 = Tetromino(renderer, &board, 16 * cellSize + cellSize, 14 * cellSize + cellSize, Type::I);
	queue2 = Tetromino(renderer, &board, 16 * cellSize + cellSize, 11 * cellSize + cellSize, Type::I);
	queue3 = Tetromino(renderer, &board, 16 * cellSize + cellSize, 7 * cellSize + cellSize, Type::I);

}

void Game::UpdateTetrominoes()
{
	currentTetromino.Reset(static_cast<Type>(queue1.getType()), 5 * cellSize + cellSize, 14 * cellSize + cellSize);
	queue1.Reset(static_cast<Type>(queue2.getType()));
	queue2.Reset(static_cast<Type>(queue3.getType()));
	queue3.Reset(static_cast<Type>(GetNext()));
}

int Game::GetNext()
{
	int returnVal = tetrominoBucket.top();
	tetrominoBucket.pop();

	if (tetrominoBucket.size() < 7)
		GenerateTetrominoes();

	return returnVal;
}

void Game::GenerateTetrominoes()
{
	int tetrominoes[7] = { 0,1,2,3,4,5,6 };

	std::shuffle(std::begin(tetrominoes), std::end(tetrominoes), std::default_random_engine());

	for (int type : tetrominoes)
		tetrominoBucket.push(type); 
}

void Game::MoveTetromino(const double dt)
{
	int x = 0, y = 0;

	if (input->IsKeyPressedRepeatable('s', dt))
	{
		if (!currentTetromino.CollisionCheck(currentTetromino.x, currentTetromino.y-cellSize))
			logicCounter = 1000;
	}
	if (input->IsKeyPressedRepeatable('a', dt)) x -= 1;
	if (input->IsKeyPressedRepeatable('d', dt)) x += 1;

	if (x != 0 || y != 0)
	{
		int intialX = currentTetromino.x;

		currentTetromino.Move(x, y);

		if (currentTetromino.CollisionCheck())
		{
			currentTetromino.x = intialX;
		}

	}
}
void Game::RotateTetromino()
{
	int x = 0, y = 0;

	if (input->IsKeyPressed('q')) currentTetromino.Rotate(true);
	if (input->IsKeyPressed('e')) currentTetromino.Rotate(false);
}


void Game::Init()
{
	for (int i = 0; i < 2; i++)
		GenerateTetrominoes();

	currentTetromino.Reset(static_cast<Type>(GetNext()), 5 * cellSize + cellSize, 14 * cellSize + cellSize);
	queue1.Reset(static_cast<Type>(GetNext()), 16 * cellSize + cellSize, 14 * cellSize + cellSize);
	queue2.Reset(static_cast<Type>(GetNext()), 16 * cellSize + cellSize, 9 * cellSize + cellSize);
	queue3.Reset(static_cast<Type>(GetNext()), 16 * cellSize + cellSize, 4 * cellSize + cellSize);

	gameOver = false;
}

void Game::Update(const double dt)
{
	if (!gameOver)
	{
		MoveTetromino(dt);
		RotateTetromino();

		if (logicCounter < 1) //update every 1 second
		{
			logicCounter += dt;
		}
		else
		{
			if (!currentTetromino.Advance())
			{
				currentTetromino.Lock();

				int firstY = 0;
				int lines = 0;

				//check for lines
				for (int y = 0; y < 4; y++)
					if (board.GetGridY(currentTetromino.y + cellSize * y) < board.boardHeight - 1 && board.GetGridY(currentTetromino.y + cellSize * y) >= 0)
					{
						bool line = true;
						for (int x = 0; x < board.boardWidth; x++)
							line &= board.grid[board.GetGridY(currentTetromino.y + cellSize * y)][x] != 0;

						if (line)
						{
							if (lines == 0) firstY = board.GetGridY(currentTetromino.y + cellSize * y);
							lines++;
						}
					}

				if (lines != 0)
				{
					printf("Number of Lines: %d, begining at Grid Y: %d \n",lines, firstY);
					board.ClearLines(firstY, lines);
				}

				UpdateTetrominoes();

				if (currentTetromino.CollisionCheck())
				{
					gameOver = true;
				}

			}
			logicCounter = 0;
		}
	}
}

void Game::Draw()
{
	board.Draw();
	currentTetromino.Draw();

	queue1.Draw();
	queue2.Draw();
	queue3.Draw();
}