#pragma once
class Renderer;
#include "Score.h"
#include "ScoreCalculator.h"
#include "GhostMino.h"
#include "InputManager.h"
#include "Font.h"
#include "GameSettings.h"
#include "TetrominoBucket.h"

/*
* Game information used throughout various states, E.g the board and score updates. Any logic specific to a single state should be kept in there.
* TODO: initalise settings via files reading and scripts
*/
struct GameData
{
	InputManager* input;
	const Renderer* renderer;

	GameSettings settings;

	Score scoreTracker;
	ScoreCalculator scoreCalc;

	Board board;
	ActiveMino currentMino;
	GhostMino ghostMino;

	Tetromino heldTetromino;

	Tetromino queue1;
	Tetromino queue2;
	Tetromino queue3;

	Font nextTitle;
	Font scoreTitle;

	Font heldTitle;
	Font score;

	Font linesTitle;
	Font lines;

	Font levelTitle;
	Font level;

	Font paused;
	Font countdown;

	TetrominoBucket tetrominoBucket;

	//logic
	bool isMinoHeld;
};

