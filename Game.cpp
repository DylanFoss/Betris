#include "Game.h"
#include <iostream>

#define BW			12
#define BH			18
#define	cellSize	7

Game::Game(const Renderer* renderer, InputManager* input)
	:renderer(renderer), input(input)
{
	board = Board(renderer, BW, BH, cellSize, 8*cellSize, cellSize);

	state = GameState::PAUSED;
	settings = GameSettings(1, 15, 1.0f, 0.3f);

	currentMino = ActiveMino(renderer, &board, board.x + 5 * cellSize , board.y + 15 * cellSize, MinoType::I);
	ghostMino = GhostMino(currentMino);
	queue1 = Tetromino(renderer, &board, board.x + 15 * cellSize + cellSize, board.y + 14 * cellSize + cellSize, MinoType::I);
	queue2 = Tetromino(renderer, &board, board.x + 15 * cellSize + cellSize, board.y + 11 * cellSize + cellSize, MinoType::I);
	queue3 = Tetromino(renderer, &board, board.x + 15 * cellSize + cellSize, board.y + 7 * cellSize + cellSize, MinoType::I);
	heldTetromino = Tetromino(renderer, &board, board.x - 6 * cellSize, board.y + 14 * cellSize, MinoType::I);

	scoreTracker = Score();
	scoreCalc = ScoreCalculator(&scoreTracker, &currentMino, &board);

	nextTitle = Font("res/fonts/pressStart2P.ttf", "NEXT", 14, 255, 255, 255, 255, 650, 550);
	heldTitle = Font("res/fonts/pressStart2P.ttf", "HOLD", 14, 255, 255, 255, 255, 60, 550);

	scoreTitle = Font("res/fonts/pressStart2P.ttf", "SCORE", 12, 255, 255, 255, 255, 30, 260);
	score = Font("res/fonts/pressStart2P.ttf", "0", 18, 255, 255, 255, 255, 30, 220);

	linesTitle = Font("res/fonts/pressStart2P.ttf", "LINES", 12, 255, 255, 255, 255, 30, 180);
	lines = Font("res/fonts/pressStart2P.ttf", "0", 18, 255, 255, 255, 255, 30, 140);

	levelTitle = Font("res/fonts/pressStart2P.ttf", "LEVEL", 12, 255, 255, 255, 255, 30, 100);
	level = Font("res/fonts/pressStart2P.ttf", "1", 18, 255, 255, 255, 255, 30, 60);

	paused = Font("res/fonts/pressStart2P.ttf", "PAUSED", 16, 255, 255, 255, 255, (160*4/2)+15, 197*4 / 2);
	countdown = Font("res/fonts/pressStart2P.ttf", "3", 22, 255, 255, 255, 255, (160 * 4 / 2) + 60, 197 * 4 / 2);

}

void Game::Init()
{
	scoreTracker = Score(settings.levelStart);
	scoreCalc = ScoreCalculator(&scoreTracker, &currentMino, &board);

	for (int i = 0; i < 2; i++)
		GenerateTetrominoes();

	currentMino.Reset(static_cast<MinoType>(GetNext()), board.x + 5 * cellSize, board.y + 15 * cellSize);
	queue1.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 14 * cellSize);
	queue2.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 9 * cellSize);
	queue3.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 4 * cellSize);

	ApplyOffset(queue1);
	ApplyOffset(queue2);
	ApplyOffset(queue3);

	ghostMino.UpdatePosition(currentMino);
	heldTetromino.Reset(MinoType::I, board.x - 6 * cellSize, board.y + 14 * cellSize);

	gameOver = false;

	stepCounter = 0;
	lockCounter = 0;
	wasHardDrop = false;
	lineClearWait = 0;
	tetrominoUpdate = false;

	IsMinoHeld = 0;
	IsHoldOnCooldown = 0;

	CalculateStepDelay();

	countdownCounter = 3;

	//hud init
	nextTitle.Init();
	heldTitle.Init();

	scoreTitle.Init();
	score.Init();

	linesTitle.Init();
	lines.Init();

	levelTitle.Init();
	level.Init();

	paused.Init();
	countdown.Init();
}

void Game::UpdateTetrominoes()
{
	currentMino.Reset(static_cast<MinoType>(queue1.getType()), board.x + 5 * cellSize, board.y + 15 * cellSize);
	queue1.Reset(static_cast<MinoType>(queue2.getType()), board.x + 15 * cellSize, board.y + 14 * cellSize);
	queue2.Reset(static_cast<MinoType>(queue3.getType()), board.x + 15 * cellSize, board.y + 9 * cellSize);
	queue3.Reset(static_cast<MinoType>(GetNext()), board.x + 15 * cellSize, board.y + 4 * cellSize);

	ApplyOffset(queue1);
	ApplyOffset(queue2);
	ApplyOffset(queue3);
}

// for the side bars, apply offsets to pieces to make them look centered 
//TODO: employ a more programatic implementation
void Game::ApplyOffset(Tetromino& mino)
{
	switch (mino.getType())
	{
		case (MinoType::I):
			mino.x -= cellSize/2;
			mino.y -= 3;
			break;
		case (MinoType::O):
			mino.x -= 3;
			break;
	}
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
		while (currentMino.Advance())
		{
			scoreCalc.IncrementHardDropCounter();
		};
		wasHardDrop = true;
		stepCounter = stepDelay;
		lockCounter = lockDelay;
	}
	else if (input->IsKeyPressedRepeatable('s', dt) || input->IsKeyPressedRepeatable('S', dt))
	{
		if (!currentMino.CollisionCheck(currentMino.x, currentMino.y - cellSize))
		{
			stepCounter = stepDelay;
			scoreCalc.IncrementSoftDropCounter();
		}
	}

	currentMino.Move(x, y);
}

void Game::RotateTetromino()
{
	if (input->IsKeyPressed('q') || input->IsKeyPressed('Q')) currentMino.Rotate(true);
	if (input->IsKeyPressed('e') || input->IsKeyPressed('E')) currentMino.Rotate(false);
}

void Game::SwapTetromino()
{
	if (input->IsKeyPressed('c') || input->IsKeyPressed('C'))
	{
		if (!IsHoldOnCooldown)
		{
			if (IsMinoHeld)
			{
				MinoType temp = currentMino.getType();
				currentMino.Reset(heldTetromino.getType(), board.x + 5 * cellSize, board.y + 15 * cellSize);
				heldTetromino.Reset(temp, board.x - 6 * cellSize, board.y + 14 * cellSize);

				IsHoldOnCooldown = true;
			}
			else
			{
				heldTetromino.Reset(currentMino.getType());

				tetrominoUpdate = true;
				IsMinoHeld = true;
			}
			ApplyOffset(heldTetromino);
			stepCounter = 0;
		}
	}
}

void Game::CalculateStepDelay()
{
	float formulaLevel = scoreTracker.GetLevel()-1;
	float lastLevel = settings.levelSoftCap-1;
	if (formulaLevel > settings.levelSoftCap) formulaLevel = lastLevel;
	stepDelay = renderer->lerp(settings.stepDelayInital, settings.stepDelayFinal, formulaLevel / lastLevel);
}

void Game::UpdateHUD()
{
	score.SetText(std::to_string(scoreTracker.GetScore()).c_str());
	lines.SetText(std::to_string(scoreTracker.GetLines()).c_str());
	level.SetText(std::to_string(scoreTracker.GetLevel()).c_str());
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

					if (currentMino.CollisionCheck())
						gameOver = true;
				}

				if (input->IsKeyPressed('p'))
				{
					state = GameState::PAUSED;
					return;
				}

				SwapTetromino();
				MoveTetromino(dt);
				RotateTetromino();
				ghostMino.UpdatePosition(currentMino);

				if (stepCounter < stepDelay) //update every 1 second
				{
					stepCounter += dt;
				}
				else
				{
					if (!currentMino.Advance())
					{
						if (wasHardDrop) { wasHardDrop = false; }
						else if ((currentMino.MovedThisTick() || currentMino.RotatedThisTick())) { lockCounter = 0; }

						if (lockCounter < lockDelay)
						{
							lockCounter += dt;
						}
						else
						{
							currentMino.Lock();

							scoreCalc.DoFullCalc(); //set flag to do a real score calulation this time.

							board.FindLines(board.GetGridY(currentMino.y));

							if (board.GetFoundLines().size() != 0)
							{
								state = GameState::CLEARLINE;

								board.GenerateLineClearAnimation();
								printf("Number of Lines: %d\n", board.linesToClear.size());
							}
							scoreCalc.SetLinesCleared(board.GetFoundLines().size());

							tetrominoUpdate = true;
							IsHoldOnCooldown = false;

							lockCounter = 0;
							stepCounter = 0;
						}
					}
					else
					{
						stepCounter = 0;
					}
					int lastLevel = scoreTracker.GetLevel();
					scoreCalc.CalculateScore();
					if (lastLevel < scoreTracker.GetLevel())
						CalculateStepDelay();
					UpdateHUD();
				}
				currentMino.Update(dt);
			}
			break;
		case (GameState::CLEARLINE):

			if (lineClearWait < 0.6f)
			{
				lineClearWait += dt;
			}
			else
			{
				board.ClearLines();
				lineClearWait = 0;
				state = GameState::PLAYPHASE;
			}

			break;

		case (GameState::PAUSED):

			if (input->IsKeyPressed('p')) state = GameState::COUNTDOWN;

			break;

		case (GameState::COUNTDOWN):

			if (countdownCounter > 0)
			{
				countdownCounter -= dt;
				countdown.SetText(std::to_string((int)std::ceil(countdownCounter)).c_str());
			}
			else
			{
				state = GameState::PLAYPHASE;
				countdownCounter = 3;
			}

			break;
		
	}
}

void Game::Draw(const double dt)
{
	switch (state)
	{
		case (GameState::PLAYPHASE):
			board.Draw(dt);
			ghostMino.Draw();
			currentMino.Draw(dt);
			queue1.Draw();
			queue2.Draw();
			queue3.Draw();

			if (IsMinoHeld) heldTetromino.Draw();

			nextTitle.Draw();
			heldTitle.Draw();

			scoreTitle.Draw();
			score.Draw();

			linesTitle.Draw();
			lines.Draw();

			levelTitle.Draw();
			level.Draw();
			break;

		case (GameState::CLEARLINE):

			board.Draw(dt);
			queue1.Draw();
			queue2.Draw();
			queue3.Draw();

			if (IsMinoHeld) heldTetromino.Draw();

			nextTitle.Draw();
			heldTitle.Draw();

			scoreTitle.Draw();
			score.Draw();

			linesTitle.Draw();
			lines.Draw();

			levelTitle.Draw();
			level.Draw();
			break;
		case (GameState::PAUSED):

			board.Draw(dt);
			ghostMino.Draw();
			currentMino.Draw(dt);
			queue1.Draw();
			queue2.Draw();
			queue3.Draw();

			if (IsMinoHeld) heldTetromino.Draw();

			nextTitle.Draw();
			heldTitle.Draw();

			scoreTitle.Draw();
			score.Draw();

			linesTitle.Draw();
			lines.Draw();

			levelTitle.Draw();
			level.Draw();

			paused.Draw();
			break;

		case (GameState::COUNTDOWN):

			board.Draw(dt);
			ghostMino.Draw();
			currentMino.Draw(dt);
			queue1.Draw();
			queue2.Draw();
			queue3.Draw();

			if (IsMinoHeld) heldTetromino.Draw();

			nextTitle.Draw();
			heldTitle.Draw();

			scoreTitle.Draw();
			score.Draw();

			linesTitle.Draw();
			lines.Draw();

			levelTitle.Draw();
			level.Draw();

			countdown.Draw();
			break;
	}
}