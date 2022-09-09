#pragma once
#include "Renderer.h"
#include <vector>
class Board
{
private:
	const Renderer* renderer;

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

	void ClearLines(int gridY, int numLines);
	void ClearLines(const std::vector<int> &linesToClear);

	void Draw();
};

