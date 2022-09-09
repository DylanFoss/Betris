#include "Board.h"
#include <algorithm>

Board::Board()
{
	renderer = nullptr;
	boardWidth = 0;
	boardHeight = 0;
	cellSize = 0;
	x = 0;
	y = 0;
	grid.resize(boardHeight, std::vector<unsigned char>(boardWidth, 0));
	timer = 0;
}

Board::Board(const Renderer* renderer, int boardWidth, int boardHeight, int cellSize, int x, int y)
	: renderer(renderer), boardWidth(boardWidth), boardHeight(boardHeight), cellSize(cellSize), x(x), y(y)
{
	grid.resize(boardHeight, std::vector<unsigned char>(boardWidth, 0));
	timer = 0;
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

void Board::ClearLines(int gridY, int numLines)
{
	for (int lines = 0; lines < numLines; lines++)
		for (int x = 0; x < boardWidth; x++)
		{
			for (int y = gridY; y < boardHeight-1; y++)
			{
				grid[y][x] = grid[y + 1][x];
			}
		}
}

void Board::ClearLines(const std::vector<int> &linesToClear)
{
	for (int lines = linesToClear.size()-1; lines > -1; lines--)
		for (int x = 0; x < boardWidth; x++)
		{
			for (int y = linesToClear.at(lines); y < boardHeight - 1; y++)
			{
				grid[y][x] = grid[y + 1][x];
			}
		}
}

void Board::Draw()
{
	if (renderer == nullptr)
	{
		printf("ERROR: Draw call attempted on object with no known renderer.");
		return;
	}

	//draw grid
	 
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
		{
			if (grid.at(i).at(j) == 0)
				/* renderer.drawSquare(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 80, 60) */ ;
			if (grid.at(i).at(j) == 0) {}
			else if (grid.at(i).at(j) == 1)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 255 - 90, 255 - 90);
			else if (grid.at(i).at(j) == 2)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 150 - 90, 200 - 90);
			else if (grid.at(i).at(j) == 3)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 165 - 90, 0);
			else if (grid.at(i).at(j) == 4)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 255 - 90, 0);
			else if (grid.at(i).at(j) == 5)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 255 - 90, 40);
			else if (grid.at(i).at(j) == 6)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 0, 0);
			else if (grid.at(i).at(j) == 7)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 0, 255 - 90);
			else if (grid.at(i).at(j) == 8)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255-90, 255 - 90, 255 - 90);
		}


	timer = 0;

	//draw border
	for (int i = 0; i < boardHeight; i++)
	{
		renderer->drawMino(cellSize, x-cellSize, y+i*cellSize, 0, 80, 60);
		renderer->drawMino(cellSize, x + boardWidth*cellSize, y + i * cellSize, 0, 80, 60);
	}

	for (int i = 0; i < boardWidth+2; i++)
	{
		renderer->drawMino(cellSize, (x - cellSize) + i*cellSize, y - cellSize, 0, 80, 60);
	}
}

void Board::Draw(const std::vector<int>& linesToClear, const double dt)
{

	if (renderer == nullptr)
	{
		printf("ERROR: Draw call attempted on object with no known renderer.");
		return;
	}

	timer += dt;
	printf("%f", timer);

	//draw grid

	for (int i = 0; i < boardHeight; i++)
	{
		bool name = false;
		for (int line : linesToClear) if (i == line) name = true;

		for (int j = 0; j < boardWidth; j++)
		{
			if (name)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255-90, 255 - 90, 255 - 90, renderer->lerp(255,0, std::min(1.0f,timer/0.5f)));
			else if (grid.at(i).at(j) == 0) {}
			else if (grid.at(i).at(j) == 1)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 255 - 90, 255 - 90);
			else if (grid.at(i).at(j) == 2)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 150 - 90, 200 - 90);
			else if (grid.at(i).at(j) == 3)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 165 - 90, 0);
			else if (grid.at(i).at(j) == 4)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 255 - 90, 0);
			else if (grid.at(i).at(j) == 5)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 0, 255 - 90, 40);
			else if (grid.at(i).at(j) == 6)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 0, 0);
			else if (grid.at(i).at(j) == 7)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 0, 255 - 90);
			else if (grid.at(i).at(j) == 8)
				renderer->drawMino(cellSize, x + (j * (cellSize)), y + (i * (cellSize)), 255 - 90, 255 - 90, 255 - 90);
		}
	}

	//draw border
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

//0, 136, 153