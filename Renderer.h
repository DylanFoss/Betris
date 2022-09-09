#pragma once
#include <stdlib.h>    
#include <GL/glut.h>

#include <algorithm>

enum class MinoType
{
	I,
	L,
	J,
	O,
	S,
	Z,
	T
};

class Renderer
{
private:

	unsigned int pixelScale;
	unsigned int screenHeight;
	unsigned int screenWidth;

public:

	Renderer(const unsigned int screenHeight, const unsigned int screenWidth, const unsigned int pixelScale)
	{
		this->screenHeight = screenHeight;
		this->screenWidth = screenWidth;
		this->pixelScale = pixelScale;
	}

	void pixel(int x, int y, int r = 0, int g = 0, int b = 0, int a = 255) const               //draw a pixel at x/y with rgb
	{
		glColor4ub(r, g, b, a);
		glBegin(GL_POINTS);
		glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
		glEnd();
	}

	void drawMino(int cellSize, int x, int y, int r, int g, int b, int a = 255) const
	{
		for (int i = 0; i < cellSize; i++)
		{
			for (int j = 0; j < cellSize; j++)
			{
				if (i == 0 && (j == 0 || j == cellSize - 1)) 
					pixel(x + (j), y + (i), std::max(r - 30, 0), std::max(g - 30, 0) , std::max(b - 30, 0), a);
				else if (i == cellSize - 1 && (j == 0 || j == cellSize - 1)) 
					pixel(x + (j), y + (i), std::min(r + 20, 255), std::min(g + 20, 255), std::min(b + 20, 255), a);
				else if (j == 0 || j == cellSize - 1) 
					pixel(x + (j), y + (i), std::max(r - 20, 0), std::max(g - 20, 0), std::max(b - 20, 0), a);		// side lines
				else if (i == 0)
					pixel(x + (j), y + (i), std::max(r - 40, 0), std::max(g - 40, 0), std::max(b - 40, 0), a);							// bottom line
				else if (i == cellSize - 1) 
					pixel(x + (j), y + (i), std::min(r + 60, 255), std::min(g + 60, 255), std::min(b + 60, 255), a);					// top line
				else pixel(x + (j), y + (i), r, g, b, a);
			}
		}
	}

	void drawMino(int cellSize, int x, int y, MinoType type, int a = 255) const
	{
		int r, g, b;

		if (type == MinoType::I) { r = 0; g = 255 - 90; b = 255 - 90; }
		else if (type == MinoType::L) { r = 0; g= 150 - 90; b = 200 - 90; }
		else if (type == MinoType::J) { r = 255 - 90; g = 165 - 90; b = 0; }
		else if (type == MinoType::O) { r = 255-90; g = 255-90; b = 0; }
		else if (type == MinoType::S) { r = 0; g = 255 - 90; b = 40; }
		else if (type == MinoType::Z) { r = 255-90; g = 0; b = 0; }
		else if (type == MinoType::T) { r = 255-90; g = 0; b = 255 - 90; }
		else { r = 0; g = 0; b = 0; }

		drawMino(cellSize, x, y, r, g, b, a);
	}

	void drawHollowSquare(int cellSize, int x, int y, int r, int g, int b) const
	{
		for (int i = 0; i < cellSize; i++)
		{
			for (int j = 0; j < cellSize; j++)
			{
				if (i == 0 && (j == 0 || j == cellSize - 1))
					pixel(x + (j), y + (i), std::max(r - 30, 0), std::max(g - 30, 0), std::max(b - 30, 0));
				else if (i == cellSize - 1 && (j == 0 || j == cellSize - 1))
					pixel(x + (j), y + (i), std::min(r + 20, 255), std::min(g + 20, 255), std::min(b + 20, 255));
				else if (j == 0 || j == cellSize - 1)
					pixel(x + (j), y + (i), std::max(r - 20, 0), std::max(g - 20, 0), std::max(b - 20, 0));		// side lines
				else if (i == 0)
					pixel(x + (j), y + (i), std::max(r - 40, 0), std::max(g - 40, 0), std::max(b - 40, 0));							// bottom line
				else if (i == cellSize - 1)
					pixel(x + (j), y + (i), std::min(r + 60, 255), std::min(g + 60, 255), std::min(b + 60, 255));					// top line
				else;
			}
		}
	}

	void Fill(int x1, int y1, int x2, int y2)
	{
		for (int y = y1; y < y2; y++)
			for (int x = x1; x < y2; x++)
				pixel(x, y, 0, 0, 0);
	}

	void clearBackground() const
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	float lerp(float a, float b, float t) const
	{
		return a * (1 - t) + b * t;
	}

};