#include <math.h>
#include <stdio.h>   
#include <iostream>  
#include <chrono>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "InputManager.h"
#include "Renderer.h"
#include "Game.h"

#include "Tetromino.h"
#include "Board.h"

#define res			1				//0=160x120 1=360x240 4=640x480
#define SW         190*res                  //screen width
#define SH         160*res                  //screen height
#define SW2        (SW/2)                   //half of screen width
#define SH2        (SH/2)                   //half of screen height
#define pixelScale 4/res                    //OpenGL pixel scale
#define GLSW       (SW*pixelScale)          //OpenGL window width
#define GLSH       (SH*pixelScale)          //OpenGL window height

#define BW			12
#define BH			18
#define	cellSize	7

typedef struct
{
	int fr1, fr2;           //frame 1 frame 2, to create constant frame rate
}t; t T;

//typedef struct
//{
//	int w, s, a, d;           
//	int wOld, aOld, sOld, dOld;
//
//	int q, e;
//	int qOld, eOld;
//
//	int space;
//	int spaceOld;
//}keys; keys K;

//unsigned char boardWidth = 12;
//unsigned char boardHeight = 18;
//unsigned char cellSize = 7;

std::chrono::time_point < std::chrono::high_resolution_clock> t1;

float logicCounter = 0;
int typeCounter = 0;

Renderer renderer = Renderer(SH, SW, pixelScale);
InputManager input = InputManager();

Board board = Board(&renderer, BW, BH, cellSize, 1 * cellSize, 1 * cellSize);
Tetromino tetromino = Tetromino(&renderer, &board, 5*cellSize+cellSize, 14*cellSize + cellSize, Type::T);

Game game = Game(&renderer, &input);


void KeysDown(unsigned char key, int x, int y)
{
	//if (key == 'w' == 1) { K.w = 1; }
	//if (key == 's' == 1) { K.s = 1; }
	//if (key == 'a' == 1) { K.a = 1; }
	//if (key == 'd' == 1) { K.d = 1; }

	//if (key == 'q' == 1) { K.q = 1; }
	//if (key == 'e' == 1) { K.e = 1; }

	//if (key == 32 == 1) { K.e = 1; }

	input.KeysDown(key, x, y);
}
void KeysUp(unsigned char key, int x, int y)
{
	//if (key == 'w' == 1) { K.w = 0; }
	//if (key == 's' == 1) { K.s = 0; }
	//if (key == 'a' == 1) { K.a = 0; }
	//if (key == 'd' == 1) { K.d = 0; }

	//if (key == 'q' == 1) { K.q = 0; }
	//if (key == 'e' == 1) { K.e = 0; }

	//if (key == 32 == 1) { K.e = 1; }

	input.KeysUp(key, x, y);
}
void KeysHeld()
{
	//K.wOld = K.w;
	//K.aOld = K.a;
	//K.sOld = K.s;
	//K.dOld = K.d;

	//K.qOld = K.q;
	//K.eOld = K.e;

}

void display()
{
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedTime = t2 - t1;
	double delta = elapsedTime.count();
	t1 = t2;

	game.Update(delta);

	//std::cout << delta << '\n';

	//Draw
	if (T.fr1 - T.fr2 >= 50)                        //only draw 20 frames/second
	{
		renderer.clearBackground();

		game.Draw();

		T.fr2 = T.fr1;
		glutSwapBuffers();
		glutReshapeWindow(GLSW, GLSH);             //prevent window scaling
	}

	input.KeysHeld();

	T.fr1 = glutGet(GLUT_ELAPSED_TIME);          //1000 Milliseconds per second

	glutPostRedisplay();
}

void init()
{
	t1 = std::chrono::high_resolution_clock::now();

	game.Init();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(GLSW / 2, GLSH / 2);
	glutInitWindowSize(GLSW, GLSH);
	glutCreateWindow("Betris - Press Alpha Build");
	glPointSize(pixelScale);                        //pixel size
	gluOrtho2D(0, GLSW, 0, GLSH);                   //origin bottom left
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeysDown);
	glutKeyboardUpFunc(KeysUp);
	glutMainLoop();
	return 0;
}