#include "GameStatePaused.h"

void GameStatePaused::Update(const double dt)
{
	if (gameData->input->IsKeyPressed('p') || gameData->input->IsKeyPressed('P'))
		ChangeState(GameStateEnum::COUNTDOWN);
}

void GameStatePaused::Draw(const double dt)
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
	
	gameData->paused.Draw();
}

void GameStatePaused::OnEnter()
{
}

void GameStatePaused::OnExit()
{
}

