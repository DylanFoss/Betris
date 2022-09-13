#include "Font.h"

Font::Font()
	:text(""), size(12), r(255), g(255), b(255), a(255), x(0), y(0), dir("res/fonts/calibri-regular.tff")
{
	if (initilised)
		Init();
}

Font::Font(const char* dir, const char* text, int size, int r, int g, int b, int a, int x, int y)
	: text(text), size(size), r(r), g(g), b(b), a(a), x(x), y(y), dir(dir)
{
	if (initilised)
		Init();
}

Font::Font(const char* text, int size, int r, int g, int b, int a, int x, int y)
	: text(text), size(size), r(r), g(g), b(b), a(a), x(x), y(y), dir("res/fonts/calibri-regular.tff")
{
	if (initilised)
		Init();
}

Font::~Font()
{
	if (initilised)
		font.clean();
}

void Font::Draw()
{
	glPushMatrix();
	glLoadIdentity();

	glColor4ub(r, g, b, a);

	textrenderer::print(font, x, y, text);

	glPopMatrix();
}

void Font::Init()
{
	font.init(dir.c_str(), size);
	initilised = true;
}