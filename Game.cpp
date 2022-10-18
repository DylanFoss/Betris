#include "Game.h"
#include <iostream>

#define BW			12
#define BH			18
#define	cellSize	7

Game::Game(const Renderer* renderer, InputManager* input)
	:renderer(renderer), input(input)
{
	gameData.renderer = renderer;
	gameData.input = input;

	gameData.board = Board(renderer, BW, BH, cellSize, 8 * cellSize, cellSize);

	gameData.settings = GameSettings(1, 15, 1.0f, 0.3f);

	gameData.currentMino = ActiveMino(renderer, &gameData.board, gameData.board.x + 5 * cellSize, gameData.board.y + 15 * cellSize, MinoType::I);
	gameData.ghostMino = GhostMino(gameData.currentMino);
	gameData.queue1 = Tetromino(renderer, &gameData.board, gameData.board.x + 15 * cellSize + cellSize, gameData.board.y + 14 * cellSize + cellSize, MinoType::I);
	gameData.queue2 = Tetromino(renderer, &gameData.board, gameData.board.x + 15 * cellSize + cellSize, gameData.board.y + 11 * cellSize + cellSize, MinoType::I);
	gameData.queue3 = Tetromino(renderer, &gameData.board, gameData.board.x + 15 * cellSize + cellSize, gameData.board.y + 7 * cellSize + cellSize, MinoType::I);
	gameData.heldTetromino = Tetromino(renderer, &gameData.board, gameData.board.x - 6 * cellSize, gameData.board.y + 14 * cellSize, MinoType::I);

	gameData.scoreTracker = Score();
	gameData.scoreCalc = ScoreCalculator(&gameData.scoreTracker, &gameData.currentMino, &gameData.board);

	gameData.nextTitle = Font("res/fonts/pressStart2P.ttf", "NEXT", 14, 255, 255, 255, 255, 650, 550);
	gameData.heldTitle = Font("res/fonts/pressStart2P.ttf", "HOLD", 14, 255, 255, 255, 255, 60, 550);

	gameData.scoreTitle = Font("res/fonts/pressStart2P.ttf", "SCORE", 12, 255, 255, 255, 255, 30, 260);
	gameData.score = Font("res/fonts/pressStart2P.ttf", "0", 18, 255, 255, 255, 255, 30, 220);

	gameData.linesTitle = Font("res/fonts/pressStart2P.ttf", "LINES", 12, 255, 255, 255, 255, 30, 180);
	gameData.lines = Font("res/fonts/pressStart2P.ttf", "0", 18, 255, 255, 255, 255, 30, 140);

	gameData.levelTitle = Font("res/fonts/pressStart2P.ttf", "LEVEL", 12, 255, 255, 255, 255, 30, 100);
	gameData.level = Font("res/fonts/pressStart2P.ttf", "1", 18, 255, 255, 255, 255, 30, 60);

	gameData.paused = Font("res/fonts/pressStart2P.ttf", "PAUSED", 16, 255, 255, 255, 255, (160 * 4 / 2) + 15, 197 * 4 / 2);
	gameData.countdown = Font("res/fonts/pressStart2P.ttf", "3", 22, 255, 255, 255, 255, (160 * 4 / 2) + 60, 197 * 4 / 2);

	manager = GameStateManager(&gameData);
	manager.AddState(&gs_playPhase);
	manager.AddState(&gs_clearLine);
	manager.AddState(&gs_countdown);
	manager.AddState(&gs_paused);
	manager.ChangeState(GameStateEnum::COUNTDOWN);

}

void Game::Init()
{
	gameData.scoreTracker = Score(gameData.settings.levelStart);
	gameData.scoreCalc = ScoreCalculator(&gameData.scoreTracker, &gameData.currentMino, &gameData.board);

	for (int i = 0; i < 2; i++)
		gameData.tetrominoBucket.GenerateTetrominoes();

	gameData.currentMino.Reset(static_cast<MinoType>(gameData.tetrominoBucket.GetNext()), gameData.board.x + 5 * cellSize, gameData.board.y + 15 * cellSize);
	gameData.queue1.Reset(static_cast<MinoType>(gameData.tetrominoBucket.GetNext()), gameData.board.x + 15 * cellSize, gameData.board.y + 14 * cellSize);
	gameData.queue2.Reset(static_cast<MinoType>(gameData.tetrominoBucket.GetNext()), gameData.board.x + 15 * cellSize, gameData.board.y + 9 * cellSize);
	gameData.queue3.Reset(static_cast<MinoType>(gameData.tetrominoBucket.GetNext()), gameData.board.x + 15 * cellSize, gameData.board.y + 4 * cellSize);

	gameData.ghostMino.UpdatePosition(gameData.currentMino);
	gameData.heldTetromino.Reset(MinoType::I, gameData.board.x - 6 * cellSize, gameData.board.y + 14 * cellSize);

	gameData.isMinoHeld = false;

	//CalculateStepDelay();

	//hud init
	gameData.nextTitle.Init();
	gameData.heldTitle.Init();

	gameData.scoreTitle.Init();
	gameData.score.Init();

	gameData.linesTitle.Init();
	gameData.lines.Init();

	gameData.levelTitle.Init();
	gameData.level.Init();

	gameData.paused.Init();
	gameData.countdown.Init();

}

void Game::Update(const double dt)
{
	manager.GetCurrentState()->Update(dt);
}

void Game::Draw(const double dt)
{
	manager.GetCurrentState()->Draw(dt);
}