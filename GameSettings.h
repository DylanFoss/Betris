#pragma once
struct GameSettings
{
	int levelStart;   // what level to start the game at.
	int levelSoftCap; // when we stop increasing speed.

	float stepDelayInital; // intial time it takes for a mino to advance
	float stepDelayFinal;	  // final time it takes for a mino to advance (on level softcap)

	GameSettings(int levelStart = 1, int levelSoftCap = 15, float stepDelayInital = 1.0f, float stepDelayFinal = 0.2f);
};

