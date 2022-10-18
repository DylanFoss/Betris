#include "GameStateCountdown.h"
#include <cmath>

GameStateCountdown::GameStateCountdown()
	:GameState(nullptr), countdownCounter(0)
{

}

GameStateCountdown::GameStateCountdown(IStateChanger* manager)
	:GameState(manager), countdownCounter(0)
{
	gameData->countdown = Font("res/fonts/pressStart2P.ttf", "3", 22, 255, 255, 255, 255, (160 * 4 / 2) + 60, 197 * 4 / 2);
	gameData->countdown.Init();
}


GameStateCountdown::~GameStateCountdown()
{
}

void GameStateCountdown::OnEnter()
{
	countdownCounter = 3;
	gameData->countdown.SetText(std::to_string((int)std::ceil(countdownCounter)).c_str());
}

void GameStateCountdown::OnExit()
{
}

void GameStateCountdown::Update(const double dt)
{
	if (countdownCounter > 0)
	{
		countdownCounter -= dt;
		gameData->countdown.SetText(std::to_string((int)std::ceil(countdownCounter)).c_str());
	}
	else
	{
		ChangeState(GameStateEnum::PLAYPHASE);
	}
}

void GameStateCountdown::Draw(const double dt)
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

	gameData->countdown.Draw();
}
