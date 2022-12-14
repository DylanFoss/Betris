#pragma once
#include "Renderer.h"
#include <vector>

class Board
{
private:
	const Renderer* renderer;
	void DrawBorder() const;
	void DrawGridMino(const int i, const int j) const;
	void AnimateClearedMino(int i, int j);

public:

	int boardWidth, boardHeight;
	std::vector<std::vector<unsigned char>> grid;
	std::vector<int> linesToClear;

	int x, y;
	int cellSize;

	Board();
	Board(const Renderer* renderer, int boardWidth, int boardHeight, int cellSize, int x, int y);
	Board(const Board& board);
	Board& operator=(const Board& other);

	int GetGridX(int x) const;
	int GetGridY(int y) const;

	bool IsElementEmpty(int x, int y);

	void FindLines(int gridY);
	const std::vector<int>& GetFoundLines() const { return linesToClear; }
	void ClearLines();

	//Drawing
	void GenerateLineClearAnimation();

	//temp flags for line clear animations
	float lineClearTimer;
	int animationType;
	bool isFadeIn;

	void Draw(const double dt);
};

