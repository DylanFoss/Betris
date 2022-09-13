#pragma once
#include <vector>
#include <string>

#include <GL/glut.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace textrenderer {

    struct font_data {
        float h;                      // Holds The Height Of The Font.
        std::vector<GLuint> textures; // Holds The Texture Id's
        GLuint list_base;             // Holds The First Display List Id

        // The Init Function Will Create A Font With
        // The Height h From The File fname.
        void init(const char* fname, unsigned int h);

        // Free All The Resources Associated With The Font.
        void clean();
    };

	//class Font {
	//public:
	//	float h;			///< Holds the height of the font.
	//	GLuint* textures;	///< Holds the texture id's 
	//	unsigned int m_vaoID[128];
	//	unsigned int m_vboID[128][3];
	//	float widthChar[128];
	//	//The init function will create a font of
	//	//of the height h from the file fname.
	//	void init(const char* fname, unsigned int h);

	//	void make_dlist(FT_Face face, char ch);
	//};

	void print(font_data const& ftfont, float x, float y, std::string const& text);

}


