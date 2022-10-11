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

#include "Font.h"

#define res			1						//0=160x120 1=360x240 4=640x480
#define SW         197*res                  //screen width
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
	std::chrono::time_point < std::chrono::high_resolution_clock> fr1, fr2;

}t; t T;

std::chrono::time_point < std::chrono::high_resolution_clock> t1;

float logicCounter = 0;

Renderer renderer = Renderer(SH, SW, pixelScale);
InputManager input = InputManager();

Game game = Game(&renderer, &input);


void KeysDown(unsigned char key, int x, int y)
{
	input.KeysDown(key, x, y);
}
void KeysUp(unsigned char key, int x, int y)
{
	input.KeysUp(key, x, y);
}

void display()
{
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedTime = t2 - t1;
	double delta = elapsedTime.count();
	t1 = t2;

	game.Update(delta);

	std::chrono::duration<double> drawTime = T.fr1 - T.fr2;
	//Draw
	if (drawTime.count() >= 0.01667f)                        //only draw 60 frames/second
	{
		renderer.clearBackground();

		game.Draw(drawTime.count());

		T.fr2 = T.fr1;
		glutSwapBuffers();
		glutReshapeWindow(GLSW, GLSH);             //prevent window scaling
	}

	input.KeysHeld();

	T.fr1 = t2;

	glutPostRedisplay();
}

void init()
{
	t1 = std::chrono::high_resolution_clock::now();
	T.fr1 = std::chrono::high_resolution_clock::now();
	T.fr2 = std::chrono::high_resolution_clock::now();

	game.Init();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(GLSW / 2, GLSH / 2);
	glutInitWindowSize(GLSW, GLSH);
	glutCreateWindow("Betris - Press Alpha Build");
	glPointSize(pixelScale);                        //pixel size
	gluOrtho2D(0, GLSW, 0, GLSH);                   //origin bottom left
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeysDown);
	glutKeyboardUpFunc(KeysUp);
	glutMainLoop();
	return 0;
}