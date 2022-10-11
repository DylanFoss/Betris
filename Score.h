#pragma once
class Score
{
private:
	int score;
	int lines;
	int level;

	int linesToLevelUp;
	int linesCounter;
public:

	Score(int level = 1, int linesToLevelUp = 10, int score = 0, int lines = 0);

	void Init();

	int GetScore() const { return score; }
	int GetLines() const { return lines; }
	int GetLevel() const { return level; }

	void UpdateScore(int newScore, int newLines);
};

