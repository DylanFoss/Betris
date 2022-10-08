#include "Board.h"
#include <algorithm>
#include <random>

Board::Board()
{
	renderer = nullptr;
	boardWidth = 0;
	boardHeight = 0;
	cellSize = 0;
	x = 0;
	y = 0;
	grid.resize(boardHeight, std::vector<unsigned char>(boardWidth, 0));
	lineClearTimer = 0;
}

Board::Board(const Renderer* renderer, int boardWidth, int boardHeight, int cellSize, int x, int y)
	: renderer(renderer), boardWidth(boardWidth), boardHeight(boardHeight), cellSize(cellSize), x(x), y(y)
{
	grid.resize(boardHeight, std::vector<unsigned char>(boardWidth, 0));
	lineClearTimer = 0;
}

Board::Board(const Board& board)
	: renderer(board.renderer)
{
	boardWidth = board.boardWidth;
	boardHeight = board.boardHeight;
	cellSize = board.cellSize;
	x = board.x;
	y = board.y;

	grid.resize(boardHeight, std::vector<unsigned char>(boardWidth, 0));
}

Board& Board::operator=(const Board& other)
{
	if (&other != this) {
		renderer = other.renderer;

		boardWidth = other.boardWidth;
		boardHeight = other.boardHeight;

		x = other.x;
		y = other.y;
		cellSize = other.cellSize;

		grid = other.grid;
	}
	return *this;
}

int Board::GetGridX(int X) const
{
	return (X - x) / cellSize;
}

int Board::GetGridY(int Y) const
{
	return (Y - y) / cellSize;
}

bool Board::IsElementEmpty(int x, int y)
{
	if (x < 0 || x > boardWidth-1 || y < 0 || y > boardHeight-1) 	//OOB check
		return false;

	if (grid[y][x] == 0)
		return true;

	return false;
}

void Board::FindLines(int gridY)
{
	for (int y = 0; y < 4; y++)
		if (gridY + y < boardHeight - 1 && gridY + y >= 0)
		{
			bool line = true;
			for (int x = 0; x < boardWidth; x++)
				line &= grid[gridY + y][x] != 0;

			if (line) 
				linesToClear.push_back(gridY + y);
		}
}

void Board::ClearLines()
{
	for (int lines = linesToClear.size()-1; lines > -1; lines--)
		for (int x = 0; x < boardWidth; x++)
		{
			for (int y = linesToClear.at(lines); y < boardHeight - 1; y++)
			{
				grid[y][x] = grid[y + 1][x];
			}
		}

	linesToClear.clear();
}


void Board::Draw(const double dt)
{
	if (renderer == nullptr)
	{
		printf("ERROR: Draw call attempted on object with no known renderer.");
		return;
	}

	if (!linesToClear.empty())
		lineClearTimer += dt;
	else
		lineClearTimer = 0;

	//draw grid

	for (int i = 0; i < boardHeight; i++)
	{
		bool animateLine = false;

		if (!linesToClear.empty())
			for (int line : linesToClear) if (i == line) animateLine = true;

		for (int j = 0; j < boardWidth; j++)
		{
			if (animateLine)
				AnimateClearedMino(i,j);
			else
				DrawGridMino(i, j);
		}
	}

	DrawBorder();
}

void Board::DrawBorder() const
{
	for (int i = 0; i < boardHeight; i++)
	{
		renderer->drawMino(cellSize, x - cellSize, y + i * cellSize, 0, 80, 60);
		renderer->drawMino(cellSize, x + boardWidth * cellSize, y + i * cellSize, 0, 80, 60);
	}

	for (int i = 0; i < boardWidth + 2; i++)
	{
		renderer->drawMino(cellSize, (x - cellSize) + i * cellSize, y - cellSize, 0, 80, 60);
	}
}

void Board::DrawGridMino(const int i, const int j) const
{
	if (grid.at(i).at(j) == 0) {}
	else renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), static_cast<MinoType>(grid.at(i).at(j) - 1), 255); //-1 as enum starts at 0 (should've used -1 for blank squares)
}

void Board::AnimateClearedMino(int i, int j)
{
	float a = 0.1f;
	float b = 0.6f;

	if (isFadeIn)
		std::swap(a, b);

	switch (animationType)
	{
		case (0):
			renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 255 - 90, 255 - 90, renderer->lerp(255, 0, std::min(1.0f, lineClearTimer / renderer->lerp(a, b, j / (float)boardWidth))));
			break;

		case (1):
			renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 255 - 90, 255 - 90, renderer->lerp(255, 0, std::min(1.0f, lineClearTimer / renderer->lerp(a, b, std::abs(j - boardWidth / 2) / (float)boardWidth))));
			break;

		case (2):
			renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 255 - 90, 255 - 90, renderer->lerp(255, 0, std::min(1.0f, lineClearTimer / renderer->lerp(a, b, std::abs((j % boardWidth / 2) - boardWidth / 2) / (float)boardWidth))));
			break;

	}
}

void Board::GenerateLineClearAnimation()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(0, 2);

	animationType = dist(mt);

	std::uniform_int_distribution<> temp(0, 2);
	isFadeIn = (bool)temp(mt);
}