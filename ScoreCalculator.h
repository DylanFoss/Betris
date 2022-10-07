#pragma once
#include "Score.h"
#include "ActiveMino.h"
class ScoreCalculator
{
private:

	int level;

	int softDropCounter;
	int hardDropCounter;

	bool wasTSpin;
	bool wasMiniTSpin;

	//int lastWallKick;

	int linesCleared;
	int comboMultiplier;

	Score* scoreTracker;
	bool fullCalculation;

	ActiveMino* currentTetromino; //used to check if a T-spin was performed
	Board* board; //ditto

	//DEBUG FLAGS
	bool countSoftDrops = true;
	bool countHardDrops = true;

public:

	ScoreCalculator();
	ScoreCalculator(Score* scoreTracker);
	ScoreCalculator(Score* scoreTracker, ActiveMino* currentTetromino, Board* board);

	void CalculateScore();
	void SoftReset();
	void Init();

	void DoFullCalc() { fullCalculation = true; }
	void SetLinesCleared(int numLines) { linesCleared = numLines; }
	void IncrementHardDropCounter() { hardDropCounter++; }
	void IncrementSoftDropCounter() { softDropCounter++; }
};

