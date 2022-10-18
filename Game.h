#pragma once
#include "Renderer.h"
#include "InputManager.h"

#include "GameData.h"

#include "GameStateEnum.h"
#include "GameStateManager.h"
#include "GameStatePlayPhase.h"
#include "GameStateCountdown.h"
#include "GameStateClearLine.h"
#include "GameStatePaused.h"

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

