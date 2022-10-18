#include "GameStatePlayPhase.h"
#include <iostream>
#include <random>

#define cellSize 7

GameStatePlayPhase::GameStatePlayPhase()
	: GameState(nullptr), stepCounter(0), lockCounter(0), gameOver(false), tetrominoUpdate(false), wasHardDrop(false), isHoldOnCooldown(false), stepDelay(1), lockDelay(0.5f)
{
}

GameStatePlayPhase::GameStatePlayPhase(IStateChanger* manager)
	: GameState(manager), stepCounter(0), lockCounter(0), gameOver(false), tetrominoUpdate(false), wasHardDrop(false), isHoldOnCooldown(false), stepDelay(1), lockDelay(0.5f)
{
}

GameStatePlayPhase::~GameStatePlayPhase()
{
}

void GameStatePlayPhase::OnEnter()
{
	std::cout << "Entering: PlayPhase\n";
}

void GameStatePlayPhase::OnExit()
{
	std::cout << "Exiting: PlayPhase\n";
}

void GameStatePlayPhase::Update(const double dt)
{
	if (!gameOver)
	{
		if (tetrominoUpdate)
		{
			UpdateTetrominoes();
			tetrominoUpdate = false;

			if (gameData->currentMino.CollisionCheck())
				gameOver = true;
		}

		if (gameData->input->IsKeyPressed('p'))
		{
			ChangeState(GameStateEnum::PAUSED);
			return;
		}

		SwapTetromino();
		MoveTetromino(dt);
		RotateTetromino();
		gameData->ghostMino.UpdatePosition(gameData->currentMino);

		if (stepCounter < stepDelay) //update every 1 second
		{
			stepCounter += dt;
		}
		else
		{
			if (!gameData->currentMino.Advance())
			{
				if (wasHardDrop) { wasHardDrop = false; }
				else if ((gameData->currentMino.MovedThisTick() || gameData->currentMino.RotatedThisTick())) { lockCounter = 0; }

				if (lockCounter < lockDelay)
				{
					lockCounter += dt;
				}
				else
				{
					gameData->currentMino.Lock();

					gameData->scoreCalc.DoFullCalc(); //set flag to do a real score calulation this time.

					gameData->board.FindLines(gameData->board.GetGridY(gameData->currentMino.y));

					if (gameData->board.GetFoundLines().size() != 0)
					{
						ChangeState(GameStateEnum::CLEARLINE);

						gameData->board.GenerateLineClearAnimation();
						printf("Number of Lines: %d\n", gameData->board.linesToClear.size());
					}
					gameData->scoreCalc.SetLinesCleared(gameData->board.GetFoundLines().size());

					tetrominoUpdate = true;
					isHoldOnCooldown = false;

					lockCounter = 0;
					stepCounter = 0;
				}
			}
			else
			{
				stepCounter = 0;
			}
			int lastLevel = gameData->scoreTracker.GetLevel();
			gameData->scoreCalc.CalculateScore();
			if (lastLevel < gameData->scoreTracker.GetLevel())
				CalculateStepDelay();
			UpdateHUD();
		}
		gameData->currentMino.Update(dt);
	}
}

void GameStatePlayPhase::Draw(const double dt)
{
	gameData->board.Draw(dt);
	gameData->ghostMino.Draw();
	gameData->currentMino.Draw(dt);
	gameData->queue1.Draw();
	gameData->queue2.Draw();
	gameData->queue3.Draw();

	if (gameData->isMinoHeld) gameData->heldTetromino.Draw();

	gameData->nextTitle.Draw();
	gameData->heldTitle.Draw();

	gameData->scoreTitle.Draw();
	gameData->score.Draw();

	gameData->linesTitle.Draw();
	gameData->lines.Draw();

	gameData->levelTitle.Draw();
	gameData->level.Draw();
}

void GameStatePlayPhase::MoveTetromino(const double dt)
{
	int x = 0, y = 0;

	if (gameData->input->IsKeyPressedRepeatable('a', dt) || gameData->input->IsKeyPressedRepeatable('A', dt)) x -= 1;
	if (gameData->input->IsKeyPressedRepeatable('d', dt) || gameData->input->IsKeyPressedRepeatable('D', dt)) x += 1;

	if (gameData->input->IsKeyPressed(32))
	{
		while (gameData->currentMino.Advance())
		{
			gameData->scoreCalc.IncrementHardDropCounter();
		};
		wasHardDrop = true;
		stepCounter = stepDelay;
		lockCounter = lockDelay;
	}
	else if (gameData->input->IsKeyPressedRepeatable('s', dt) || gameData->input->IsKeyPressedRepeatable('S', dt))
	{
		if (!gameData->currentMino.CollisionCheck(gameData->currentMino.x, gameData->currentMino.y - cellSize)) 
		{
			stepCounter = stepDelay;
			gameData->scoreCalc.IncrementSoftDropCounter();
		}
	}

	gameData->currentMino.Move(x, y);
}

void GameStatePlayPhase::RotateTetromino()
{
	if (gameData->input->IsKeyPressed('q') || gameData->input->IsKeyPressed('Q')) gameData->currentMino.Rotate(true);
	if (gameData->input->IsKeyPressed('e') || gameData->input->IsKeyPressed('E')) gameData->currentMino.Rotate(false);
}

void GameStatePlayPhase::SwapTetromino()
{
	if (gameData->input->IsKeyPressed('c') || gameData->input->IsKeyPressed('C'))
	{
		if (!isHoldOnCooldown)
		{
			if (gameData->isMinoHeld)
			{
				MinoType temp = gameData->currentMino.getType();
				gameData->currentMino.Reset(gameData->heldTetromino.getType(), gameData->board.x + 5 * cellSize, gameData->board.y + 15 * cellSize);
				gameData->heldTetromino.Reset(temp, gameData->board.x - 6 * cellSize, gameData->board.y + 14 * cellSize);

				isHoldOnCooldown = true;
			}
			else
			{
				gameData->heldTetromino.Reset(gameData->currentMino.getType());

				tetrominoUpdate = true;
				gameData->isMinoHeld = true;
			}
			ApplyOffset(gameData->heldTetromino);
			stepCounter = 0;
		}
	}
}

void GameStatePlayPhase::CalculateStepDelay()
{
	float formulaLevel = gameData->scoreTracker.GetLevel() - 1;
	float lastLevel = gameData->settings.levelSoftCap - 1;
	if (formulaLevel > gameData->settings.levelSoftCap) formulaLevel = lastLevel;
	stepDelay = gameData->renderer->lerp(gameData->settings.stepDelayInital, gameData->settings.stepDelayFinal, formulaLevel / lastLevel);
}

void GameStatePlayPhase::UpdateHUD()
{
	gameData->score.SetText(std::to_string(gameData->scoreTracker.GetScore()).c_str());
	gameData->lines.SetText(std::to_string(gameData->scoreTracker.GetLines()).c_str());
	gameData->level.SetText(std::to_string(gameData->scoreTracker.GetLevel()).c_str());
}

void GameStatePlayPhase::UpdateTetrominoes()
{
	gameData->currentMino.Reset(static_cast<MinoType>(gameData->queue1.getType()), gameData->board.x + 5 * cellSize, gameData->board.y + 15 * cellSize);
	gameData->queue1.Reset(static_cast<MinoType>(gameData->queue2.getType()), gameData->board.x + 15 * cellSize, gameData->board.y + 14 * cellSize);
	gameData->queue2.Reset(static_cast<MinoType>(gameData->queue3.getType()), gameData->board.x + 15 * cellSize, gameData->board.y + 9 * cellSize);
	gameData->queue3.Reset(static_cast<MinoType>(gameData->tetrominoBucket.GetNext()), gameData->board.x + 15 * cellSize, gameData->board.y + 4 * cellSize);

	ApplyOffset(gameData->queue1);
	ApplyOffset(gameData->queue2);
	ApplyOffset(gameData->queue3);
}


// for the side bars, apply offsets to pieces to make them look centered 
//TODO: employ a more programatic implementation
void GameStatePlayPhase::ApplyOffset(Tetromino& mino)
{
	switch (mino.getType())
	{
	case (MinoType::I):
		mino.x -= cellSize / 2;
		mino.y -= 3;
		break;
	case (MinoType::O):
		mino.x -= 3;
		break;
	}
}
