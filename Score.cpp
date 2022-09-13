#include "Score.h"

Score::Score()
	: level(1), score(0), lines(0)
{
}

void Score::UpdateScore(int newScore, int newLines)
{
	score += newScore;
	lines += newLines;
}