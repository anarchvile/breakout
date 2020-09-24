#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include <vector>

class GameObject
{
public:
	GLuint LevelWidth, LevelHeight, NumBlocksX, NumBlocksY, VerticalSpace;
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation, ID;
	GLboolean IsActive;
	Texture2D Sprite;
	GameObject();
	GameObject(GLfloat ID, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Draw(SpriteRenderer &renderer);
	void Init(GLuint levelWidth, GLuint levelHeight, GLuint numBlocksX, GLuint numBlocksY, GLuint verticalSpace);
	std::vector<GameObject> Bricks;
};

#endif
