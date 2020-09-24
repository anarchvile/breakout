#include "pch.h"
#include "game_level.h"

void GameLevel::Load(GLuint levelWidth, GLuint levelHeight, GLuint numBlocksX, GLuint numBlocksY, GLuint verticalSpace)
{
	this->object.Bricks.clear();
	this->object.Init(levelWidth, levelHeight, numBlocksX, numBlocksY, verticalSpace);
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
	for (GameObject &tile : this->object.Bricks)
		if (tile.IsActive)
			tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
	for (GameObject &tile : this->object.Bricks)
		if (tile.IsActive)
			return GL_FALSE;
	return GL_TRUE;
}