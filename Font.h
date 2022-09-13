#pragma once
#include "TextRenderer.h"
class Font
{
private:

	std::string text;
	textrenderer::font_data font;
	int size;
	std::string dir;

	int x, y;
	int r, g, b, a;

	bool initilised = false;

public:

	Font();
	Font(const char* dir, const char* text = "", int size = 12, int r = 255, int g = 255, int b = 255, int a = 255, int x = 0, int y = 0);
	Font(const char* text, int size, int r, int g, int b, int a, int x, int y);
	~Font();

	void Draw();
	void Init();

	void SetText(const char* newText) { text = newText; }
	void SetX(int newX) { x = newX; }
	void SetY(int newY) { y = newY; }

	int GetX() const { return x; }
	int GetY() const { return y; }
	const std::string& GetText() const { return text; }

};

