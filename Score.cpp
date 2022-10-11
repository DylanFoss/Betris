#include "Score.h"

Score::Score(int level, int linesToLevelUp, int score, int lines)
	: score(score), lines(lines), level(level), linesToLevelUp(linesToLevelUp), linesCounter(0)
{
}

void Score::UpdateScore(int newScore, int newLines)
{
	score += newScore;
	lines += newLines;

	linesCounter += newLines;
	if (linesCounter > linesToLevelUp)
	{
		level++;
		linesCounter = linesCounter - linesToLevelUp;
	}
}