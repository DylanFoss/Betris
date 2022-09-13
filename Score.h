#pragma once
class Score
{
private:
	int score;
	int lines;
	int level;
public:

	Score();

	void Init();

	int GetScore() const { return score; }
	int GetLines() const { return lines; }
	int GetLevel() const { return level; }

	void UpdateScore(int newScore, int newLines);
};

