#include "ScoreCalculator.h"
#include <iostream>

ScoreCalculator::ScoreCalculator()
	: scoreTracker(nullptr),level(1), softDropCounter(0), hardDropCounter(0), linesCleared(0), comboMultiplier(-1), fullCalculation(false)
{

}

ScoreCalculator::ScoreCalculator(Score* scoreTracker)
	: scoreTracker(scoreTracker), level(1), softDropCounter(0), hardDropCounter(0), linesCleared(0), comboMultiplier(-1), fullCalculation(false)
{

}

void ScoreCalculator::CalculateScore()
{
	int roundScore = 0;

	//calculate drops
	if (countSoftDrops)
		roundScore += softDropCounter;

	if (fullCalculation)
	{
		if (countHardDrops)
			roundScore += hardDropCounter * 2;

		//line clears

		if (linesCleared == 0)
		{
			comboMultiplier = -1;
		}
		else
		{
			switch (linesCleared)
			{
			case(1):
				roundScore += 100 * level;
				break;
			case(2):
				roundScore += 300 * level;
				break;
			case(3):
				roundScore += 500 * level;
				break;
			case(4):
				roundScore += 800 * level;
				break;
			}

			comboMultiplier++;
		}

		//Tspins TODO

		//Back TO Back TODO

		//Combo
		if (comboMultiplier > 0)
			roundScore += 50 * comboMultiplier * level;
	}

	scoreTracker->UpdateScore(roundScore, linesCleared);
	SoftReset();
}

void ScoreCalculator::SoftReset()
{
	softDropCounter = 0;
	hardDropCounter = 0;
	linesCleared = 0;

	fullCalculation = false;
}

void ScoreCalculator::Init()
{
}
