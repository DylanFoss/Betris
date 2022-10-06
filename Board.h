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

	int x, y;
	int cellSize;

	Board();
	Board(const Renderer* renderer, int boardWidth, int boardHeight, int cellSize, int x, int y);
	Board(const Board& board);
	Board& operator=(const Board& other);

	int GetGridX(int x) const;
	int GetGridY(int y) const;

	bool IsElementEmpty(int x, int y);

	void ClearLines(int gridY, int numLines);
	void ClearLines(const std::vector<int>& linesToClear);

	void GenerateLineClearAnimation();

	//Drawing

	//temp flags for line clear animations
	float timer;
	int animationType;
	bool isFadeIn;

	void Draw();
	void Draw(const std::vector<int> &linesToClear, const double dt);
};

