#include "Game.h"

#define BW			12
#define BH			18
#define	cellSize	7

Game::Game(const Renderer* renderer, InputManager* input)
	:renderer(renderer), input(input)
{
	state = GameState::PLAYPHASE;

	board = Board(renderer, BW, BH, cellSize, 8*cellSize, cellSize);

	currentTetromino = Tetromino(renderer, &board, board.x + 5 * cellSize , board.y + 15 * cellSize, MinoType::I);
	ghostPiece = GhostPiece(currentTetromino);
	queue1 = Tetromino(renderer, &board, board.x + 15 * cellSize + cellSize, board.y + 14 * cellSize + cellSize, MinoType::I);
	queue2 = Tetromino(renderer, &board, board.x + 15 * cellSize + cellSize, board.y + 11 * cellSize + cellSize, MinoType::I);
	queue3 = Tetromino(renderer, &board, board.x + 15 * cellSize + cellSize, board.y + 7 * cellSize + cellSize, MinoType::I);

	Next = Font("res/fonts/pressStart2P.ttf", "Next", 14, 255, 255, 255, 255, 650, 550);
	Score = Font("res/fonts/pressStart2P.ttf", "Score", 14, 255, 255, 255, 255, 50, 200);
	Held = Font("res/fonts/pressStart2P.ttf", "Hold", 14, 255, 255, 255, 255, 50, 550);

}

void Game::UpdateTetrominoes()
{
	currentTetromino.Reset(static_cast<MinoType>(queue1.getType()), board.x + 5 * cellSize, board.y + 15 * cellSize);
	queue1.Reset(static_cast<MinoType>(queue2.getType()));
	queue2.Reset(static_cast<MinoType>(queue3.getType()));
	queue3.Reset(static_cast<MinoType>(GetNext()));
}

int Game::GetNext()
{
	int returnVal = tetrominoBucket.front();
	tetrominoBucket.pop();

	if (tetrominoBucket.size() < 7)
		GenerateTetrominoes();

	return returnVal;
}

void Game::GenerateTetrominoes()
{
	int tetrominoes[7] = { 0,1,2,3,4,5,6 };
	std::random_device rd;
	unsigned seed = rd();
	std::shuffle(std::begin(tetrominoes), std::end(tetrominoes), std::default_random_engine(seed));

	for (int type : tetrominoes)
		tetrominoBucket.push(type); 
}

void Game::MoveTetromino(const double dt)
{
	int x = 0, y = 0;

	if (input->IsKeyPressedRepeatable('a', dt) || input->IsKeyPressedRepeatable('A', dt)) x -= 1;
	if (input->IsKeyPressedRepeatable('d', dt) || input->IsKeyPressedRepeatable('D', dt)) x += 1;

	if (input->IsKeyPressed(32))
	{
		while (currentTetromino.Advance());
		stepCounter = 1000;
	}
	else if (input->IsKeyPressedRepeatable('s', dt) || input->IsKeyPressedRepeatable('S', dt))
	{
		if (!currentTetromino.CollisionCheck(currentTetromino.x, currentTetromino.y - cellSize))
			stepCounter = 1000;
	}

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

	if (input->IsKeyPressed('q') || input->IsKeyPressed('Q')) currentTetromino.Rotate(true);
	if (input->IsKeyPressed('e') || input->IsKeyPressed('E')) currentTetromino.Rotate(false);
}


void Game::Init()
{
	for (int i = 0; i < 2; i++)
		GenerateTetrominoes();

	currentTetromino.Reset(static_cast<MinoType>(GetNext()), board.x + 5 * cellSize, board.y + 15 * cellSize);
	ghostPiece.UpdatePosition(currentTetromino);
	queue1.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 14 * cellSize);
	queue2.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 9 * cellSize);
	queue3.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 4  * cellSize);

	gameOver = false;

	stepCounter = 0;
	lineClearWait = 0;
	tetrominoUpdate = false;

	Next.Init();
	Score.Init();
	Held.Init();
}

void Game::Update(const double dt)
{
	switch (state)
	{

		case (GameState::PLAYPHASE):
			if (!gameOver)
			{
				if (tetrominoUpdate)
				{
					UpdateTetrominoes();

					tetrominoUpdate = false;

					if (currentTetromino.CollisionCheck())
						gameOver = true;
				}

				MoveTetromino(dt);
				RotateTetromino();
				ghostPiece.UpdatePosition(currentTetromino);

				if (stepCounter < 1) //update every 1 second
				{
					stepCounter += dt;
				}
				else
				{

					if (!currentTetromino.Advance())
					{
						currentTetromino.Lock();

						//check for lines
						for (int y = 0; y < 4; y++)
							if (board.GetGridY(currentTetromino.y) + y < board.boardHeight - 1 && board.GetGridY(currentTetromino.y) + y >= 0)
							{
								bool line = true;
								for (int x = 0; x < board.boardWidth; x++)
									line &= board.grid[board.GetGridY(currentTetromino.y) + y][x] != 0;

								if (line)
								{
									linesToClear.push_back(board.GetGridY(currentTetromino.y) + y);
								}
							}

						if (linesToClear.size() != 0)
						{
							state = GameState::CLEARLINE;
							board.GenerateLineClearAnimation();
							printf("Number of Lines: %d\n", linesToClear.size());
						}

						tetrominoUpdate = true;

					}
					stepCounter = 0;
				}
			}
			break;
		case (GameState::CLEARLINE):

			if (lineClearWait < 0.6f)
			{
				lineClearWait += dt;
			}
			else
			{
				board.ClearLines(linesToClear);
				linesToClear.clear();
				lineClearWait = 0;
				state = GameState::PLAYPHASE;
			}

			break;
		
	}
}

void Game::Draw(const double dt)
{
	switch (state)
	{
		case (GameState::PLAYPHASE):
			board.Draw();
			ghostPiece.Draw();
			currentTetromino.Draw();
			queue1.Draw();
			queue2.Draw();
			queue3.Draw();
			break;

		case (GameState::CLEARLINE):
			board.Draw(linesToClear, dt);
			queue1.Draw();
			queue2.Draw();
			queue3.Draw();
			break;
	}

	Next.Draw();
	Score.Draw();
	Held.Draw();
}