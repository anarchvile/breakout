#include "pch.h"
#include <iostream>
#include <GL/glew.h>
#include <glut.h>

#include "resource_manager.h"
#include "game.h"
#include "game_level.h"

#include <ctime>

#define FPS 30

GLuint levelWidth = 600, levelHeight = 600, numBlocksX = 10, numBlocksY = 10, verticalSpace = 5;
GLfloat deltaTime = 0, velocity;

Game Breakout(levelWidth, levelHeight, numBlocksX, numBlocksY, verticalSpace);

void startGame(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);

	if (key == 'r' || key == 'R')
	{
		Breakout.ResetLevel();
		Breakout.ResetPlayer();
		Breakout.Start = GL_FALSE;
	}

	if (Breakout.Start == GL_FALSE)
	{
		if (key == 32)
		{
			Breakout.Start = GL_TRUE;
		}
	}
}

void pressKey(int key, int x, int y)
{
	if (Breakout.Start == GL_TRUE)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			velocity = -Breakout.PLAYER_VELOCITY / FPS;
			break;
		case GLUT_KEY_RIGHT:
			velocity = Breakout.PLAYER_VELOCITY / FPS;
			break;
		}
	}
}

void releaseKey(int key, int x, int y)
{
	if (Breakout.Start == GL_TRUE)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			velocity = 0;
			break;
		}
	}
}

void reshapeWindow(int w, int h)
{
	if (h == 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if ((float)w >= levelWidth && (float)h >= levelHeight) gluOrtho2D(0, 10 / levelWidth * w, 0, 10 / levelHeight * h);
	else gluOrtho2D(0, 10, 0, 10);
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	deltaTime = 1.0f / (10 * FPS);
	glClear(GL_COLOR_BUFFER_BIT);
	Breakout.ProcessInput(velocity);
	Breakout.Update(deltaTime, Breakout.Start);
	Breakout.Render();
	glutSwapBuffers();
}

void idle(int)
{
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(startGame);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, idle, 0);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Breakout_OOP");

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Breakout.Init();
	Breakout.State = GAME_ACTIVE;

	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshapeWindow);
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, idle, 0);

	glutMainLoop();
	ResourceManager::Clear();
	return 1;
}
