#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm.hpp>

#include "game.h"
#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel
{
public:
	GameLevel() {}
	GameObject object;
	void Load(GLuint levelWidth, GLuint levelHeight, GLuint numBlocksX, GLuint numBlocksY, GLuint verticalSpace);
	void Draw(SpriteRenderer &renderer);
	GLboolean IsCompleted();
};

#endif // !GAMELELEV_H
