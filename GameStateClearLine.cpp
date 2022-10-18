#include "GameStateClearLine.h"
#include "GameData.h"


GameStateClearLine::GameStateClearLine()
	:GameState(), lineClearWait(0)
{
}

GameStateClearLine::GameStateClearLine(IStateChanger* manager)
	: GameState(manager), lineClearWait(0)
{
}

GameStateClearLine::~GameStateClearLine()
{
}

void GameStateClearLine::OnEnter()
{
	lineClearWait = 0;
}

void GameStateClearLine::OnExit()
{
}

void GameStateClearLine::Update(const double dt)
{
	if (lineClearWait < 0.6f)
	{
		lineClearWait += dt;
	}
	else
	{
		gameData->board.ClearLines();
		lineClearWait = 0;
		ChangeState(GameStateEnum::PLAYPHASE);
	}
}

void GameStateClearLine::Draw(const double dt)
{
	gameData->board.Draw(dt);
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
