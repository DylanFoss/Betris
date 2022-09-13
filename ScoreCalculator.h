#pragma once
#include "Score.h"
class ScoreCalculator
{
private:

	int level;

	int softDropCounter;
	int hardDropCounter;
	int linesCleared;
	int comboMultiplier;

	Score* scoreTracker;

	bool fullCalculation;

	//DEBUG FLAGS
	bool countSoftDrops = true;
	bool countHardDrops = true;

public:

	ScoreCalculator();
	ScoreCalculator(Score* scoreTracker);

	void CalculateScore();
	void SoftReset();
	void Init();

	void DoFullCalc() { fullCalculation = true; }
	void SetLinesCleared(int numLines) { linesCleared = numLines; }
	void IncrementHardDropCounter() { hardDropCounter++; }
	void IncrementSoftDropCounter() { softDropCounter++; }
};

