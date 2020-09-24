#include "pch.h"
#include "ball_object.h"

BallObject::BallObject()
	: GameObject(), Radius(9.0f) {}

BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(0, pos, glm::vec2 (radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius (radius) {}

glm::vec2 BallObject::Move(GLfloat dt, GLboolean start, GLuint window_width)
{
	if (start == GL_TRUE)
	{
		this->Position += this->Velocity * dt;
		if (this->Position.x <= 0)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0;
		}

		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}

		if (this->Position.y <= 0)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0;
		}
	}
	
	return this->Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}