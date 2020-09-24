#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <GL/glew.h>
#include <glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "game_object.h"

class BallObject : public GameObject
{
public:
	GLfloat Radius;
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	glm::vec2 Move(GLfloat dt, GLboolean start, GLuint window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif