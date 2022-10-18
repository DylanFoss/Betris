#pragma once

#include <array>
#include <vector>
#include <stack>
#include <algorithm>

#include "Renderer.h"
#include "InputManager.h"
#include "GameSettings.h"

#include "Score.h"
#include "ScoreCalculator.h"

#include "Board.h"

#include "Tetromino.h"
#include "ActiveMino.h"
#include "GhostMino.h"
#include "Font.h"

#include "GameStateEnum.h"
#include "GameStateManager.h"
#include "GameStatePlayPhase.h"
#include "GameStateCountdown.h"
#include "GameStateClearLine.h"
#include "GameStatePaused.h"
#include "GameData.h"

class Game
{
private:

	const Renderer* renderer;
	InputManager* input;

	GameData gameData;

	GameStateManager manager;
	GameStateCountdown gs_countdown;
	GameStatePlayPhase gs_playPhase;
	GameStateClearLine gs_clearLine;
	GameStatePaused gs_paused;

public:

	Game(const Renderer* renderer, InputManager* input);

	void Init();
	void Update(const double deltaTime);
	void Draw(const double deltaTime);
};

