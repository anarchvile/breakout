#include "pch.h"
#include "game_object.h"
#include <iostream>

GameObject::GameObject()
	:ID(0), Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsActive(true){ }

GameObject::GameObject(GLfloat ID, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	:ID(ID), Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsActive(true){}

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::Init(GLuint levelWidth, GLuint levelHeight, GLuint numBlocksX, GLuint numBlocksY, GLuint verticalSpace)
{
	int hh = 9 - verticalSpace;
	int ii = 0;
	int jj = -1;
	int kk = 0;
	int ll = 1;
	int mm = 2;

	GLfloat blockSizeX = (GLfloat)levelWidth / numBlocksX;
	GLfloat blockSizeY = (GLfloat)levelHeight / numBlocksY;

	glm::vec3 color;

	for (GLuint y = 0; y < verticalSpace; ++y)
	{
		++hh;
		for (GLuint x = 0; x < numBlocksX; ++x)
		{
			++ii;
			if (jj <= (int)numBlocksX - 2) ++jj;
			else jj = 0;

			if (numBlocksX % 3 == 0)
			{
				int ii = (10 - jj) + hh * numBlocksX;
				if (kk < 3)
				{
					if (ii % 3 == kk) color = glm::vec3(0, 1, 0);
				}

				else kk = 0;

				if (ll < 3)
				{
					if (ii % 3 == ll) color = glm::vec3(1, 0, 0);
				}

				else ll = 0;

				if (mm < 3)
				{
					if (ii % 3 == mm) color = glm::vec3(0, 0, 1);
				}

				else mm = 0;
			}

			else if (numBlocksX % 3 == 1)
			{
				if (ii % 3 == 0) color = glm::vec3(0, 0, 1);
				else if (ii % 3 == 1) color = glm::vec3(1, 0, 0);
				else if (ii % 3 == 2) color = glm::vec3(0, 1, 0);
			}

			else if (numBlocksX % 3 == 2)
			{
				int ii = (10 - jj) + hh * numBlocksX;
				if (ii % 3 == 0) color = glm::vec3(0, 0, 1);
				else if (ii % 3 == 1) color = glm::vec3(0, 1, 0);
				else if (ii % 3 == 2) color = glm::vec3(1, 0, 0);
			}

			glm::vec2 pos(blockSizeX * x, blockSizeY * y);
			glm::vec2 size(blockSizeX, blockSizeY);
			GameObject obj(jj, pos, size, ResourceManager::GetTexture("block"), color);
			obj.IsActive = GL_TRUE;
			this->Bricks.push_back(obj);
		}
		++kk;
		++ll;
		++mm;
	}
}