#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glut.h>
#include "game_level.h"

#include <vector>
#include <tuple>

//current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	LEFT, 
	DOWN
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game
{
public:
	//game state and initial conditions
	GameState State;
	GLboolean Start = GL_FALSE;
	GLuint Width, Height, NumBlocksX, NumBlocksY, VerticalSpace;
	glm::vec2 PLAYER_SIZE;
	glm::vec2 INITIAL_BALL_VELOCITY;
	GLfloat PLAYER_VELOCITY, BALL_RADIUS;
	//constructor/Destructor
	Game(GLuint width, GLuint height, GLuint numBlocksX, GLuint numBlocksY, GLuint verticalSpace);
	~Game();
	//initialize game state (load all shaders/textures/levels)
	void Init();
	//gameLoop
	void ProcessInput(GLfloat velocity);
	void Update(GLfloat dt, GLboolean start);
	void Render();
	void DoCollisions();
	void ResetLevel();
	void ResetPlayer();
	void WinGame();
};

#endif