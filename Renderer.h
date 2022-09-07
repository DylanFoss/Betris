#pragma once
#include <stdlib.h>    
#include <GL/glut.h>

#include <algorithm>

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

	void pixel(int x, int y, int c) const               //draw a pixel at x/y with rgb
	{
		int rgb[3];
		if (c == 0) { rgb[0] = 255; rgb[1] = 255; rgb[2] = 0; } //Yellow	
		if (c == 1) { rgb[0] = 160; rgb[1] = 160; rgb[2] = 0; } //Yellow darker	
		if (c == 2) { rgb[0] = 0; rgb[1] = 255; rgb[2] = 0; } //Green	
		if (c == 3) { rgb[0] = 0; rgb[1] = 160; rgb[2] = 0; } //Green darker	
		if (c == 4) { rgb[0] = 0; rgb[1] = 255; rgb[2] = 255; } //Cyan	
		if (c == 5) { rgb[0] = 0; rgb[1] = 160; rgb[2] = 160; } //Cyan darker
		if (c == 6) { rgb[0] = 160; rgb[1] = 100; rgb[2] = 0; } //brown	
		if (c == 7) { rgb[0] = 110; rgb[1] = 50; rgb[2] = 0; } //brown darker
		if (c == 8) { rgb[0] = 0; rgb[1] = 60; rgb[2] = 130; } //background 
		glColor3ub(rgb[0], rgb[1], rgb[2]);
		glBegin(GL_POINTS);
		glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
		glEnd();
	}

	void pixel(int x, int y, int r = 0, int g = 0, int b = 0) const               //draw a pixel at x/y with rgb
	{
		glColor3ub(r, g, b);
		glBegin(GL_POINTS);
		glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
		glEnd();
	}

	void drawSquare(int cellSize, int x, int y, int r, int g, int b) const
	{
		for (int i = 0; i < cellSize; i++)
		{
			for (int j = 0; j < cellSize; j++)
			{
				if (i == 0 && (j == 0 || j == cellSize - 1)) 
					pixel(x + (j), y + (i), std::max(r - 30, 0), std::max(g - 30, 0) , std::max(b - 30, 0));
				else if (i == cellSize - 1 && (j == 0 || j == cellSize - 1)) 
					pixel(x + (j), y + (i), std::min(r + 20, 255), std::min(g + 20, 255), std::min(b + 20, 255));
				else if (j == 0 || j == cellSize - 1) 
					pixel(x + (j), y + (i), std::max(r - 20, 0), std::max(g - 20, 0), std::max(b - 20, 0));		// side lines
				else if (i == 0)
					pixel(x + (j), y + (i), std::max(r - 40, 0), std::max(g - 40, 0), std::max(b - 40, 0));							// bottom line
				else if (i == cellSize - 1) 
					pixel(x + (j), y + (i), std::min(r + 60, 255), std::min(g + 60, 255), std::min(b + 60, 255));					// top line
				else pixel(x + (j), y + (i), r, g, b);
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

};