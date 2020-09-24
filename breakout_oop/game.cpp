#include "pch.h"
#include "resource_manager.h"
#include "game.h"
#include "ball_object.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctime>

GameObject *Player;
BallObject *Ball;
GameLevel one;
SpriteRenderer *Renderer;

std::vector<GLuint> numCollidedBricks;

Game::Game(GLuint width, GLuint height, GLuint numBlocksX, GLuint numBlocksY, GLuint verticalSpace)
	: State(GAME_ACTIVE), Width(width), Height(height), NumBlocksX(numBlocksX), NumBlocksY(numBlocksY), VerticalSpace(verticalSpace)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Ball;
}

int randomNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void Game::Init()
{
	this->PLAYER_SIZE = glm::vec2(120, 12);
	this->PLAYER_VELOCITY = 500.0f;
	this->BALL_RADIUS = 9.0f;
	glm::vec2 vel = glm::vec2(randomNumber(-350, 350), randomNumber(-350, -100));
	glm::vec2 normVel = glm::normalize(vel);
	this->INITIAL_BALL_VELOCITY = glm::vec2(350 * normVel.x, 350 * normVel.y);
	ResourceManager::LoadShader("vertex.txt", "fragment.txt", nullptr, "sprite");
	Shader spriteShader = ResourceManager::GetShader("sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	spriteShader.Use().SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
	ResourceManager::LoadTexture("paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTexture("awesomeface_01.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("background.jpg", GL_FALSE, "background");

	glm::vec2 playerPos = glm::vec2(0.5f * this->Width - 0.5f * PLAYER_SIZE.x, 0.9f * this->Height - PLAYER_SIZE.y);
	Player = new GameObject(0, playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - this->BALL_RADIUS, -this->BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, this->BALL_RADIUS, this->INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));

	Renderer = new SpriteRenderer(spriteShader);
	if (this->VerticalSpace >= this->NumBlocksY) this->VerticalSpace = this->NumBlocksY - 1;
	one.Load(this->Width, this->Height, this->NumBlocksX, this->NumBlocksY, this->VerticalSpace);
}

void Game::Update(GLfloat dt, GLboolean start)
{
	for (int i = 0; i < 10; ++i)
	{
		Ball->Move(dt, start, this->Width);
		this->DoCollisions();
	}
	if (Ball->Position.y >= this->Height)
	{
		this->ResetLevel();
		this->ResetPlayer();
		this->Start = GL_FALSE;
	}
	WinGame();
}


void Game::ProcessInput(GLfloat velocity)
{
	if (this->State == GAME_ACTIVE)
	{
		if (Player->Position.x > -0.1f && Player->Position.x < this->Width - 0.99f * Player->Size.x) Player->Position.x += velocity;
		if (Player->Position.x <= -0.1f && GLUT_KEY_LEFT) Player->Position.x += 0;
		if (Player->Position.x <= -0.1f && GLUT_KEY_RIGHT) Player->Position.x -= velocity;
		if (Player->Position.x >= this->Width - 0.99f * Player->Size.x && GLUT_KEY_RIGHT) Player->Position.x += 0;
		if (Player->Position.x >= this->Width - 0.99f * Player->Size.x && GLUT_KEY_LEFT) Player->Position.x -= velocity;
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Texture2D backgroundTexture = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(backgroundTexture, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0);
		Player->Draw(*Renderer);
		one.Draw(*Renderer);
		Ball->Draw(*Renderer);
	}
}

float clamp(float value, float min, float max)
{
	return fmaxf(min, fminf(max, value));
}

void Game::ResetLevel()
{
	one.Load(this->Width, this->Height, this->NumBlocksX, this->NumBlocksY, this->VerticalSpace);
	numCollidedBricks.clear();
}

void Game::ResetPlayer()
{
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(0.5f * this->Width - 0.5f * PLAYER_SIZE.x, 0.9f * this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}

void Game::WinGame()
{
	if (one.IsCompleted())
	{
		this->State = GAME_WIN;
		MessageBox(NULL, L"Level 1 Complete\nThanks for playing!", L"Breakout", MB_OK | MB_ICONASTERISK);
		exit(0);
	}
}

Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
	for (GameObject &box : one.object.Bricks)
	{
		if (box.IsActive)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))
			{
				box.IsActive = false;
				numCollidedBricks.push_back(box.ID);
				Direction direction = std::get<1>(collision);
				glm::vec2 difference_vector = std::get<2>(collision);
				if (direction == LEFT || direction == RIGHT)
				{
					if (numCollidedBricks.size() == 2 && abs((int)numCollidedBricks.front() - (int)numCollidedBricks.back()) == this->NumBlocksX) Ball->Velocity.x = Ball->Velocity.x;
					else Ball->Velocity.x = -Ball->Velocity.x;
					GLfloat penetration = Ball->Radius - std::abs(difference_vector.x);
					if (direction == LEFT) Ball->Position.x += penetration;
					else Ball->Position.x -= penetration;
				}

				else if (direction == UP || direction == DOWN)
				{
					if (numCollidedBricks.size() == 2 && abs((int)numCollidedBricks.front() - (int)numCollidedBricks.back()) == 1) Ball->Velocity.y = Ball->Velocity.y;
					else Ball->Velocity.y = -Ball->Velocity.y;
					GLfloat penetration = Ball->Radius - std::abs(difference_vector.y);
					if (direction == UP) Ball->Position.y += penetration;
					else Ball->Position.y -= penetration;
				}
			}
		}
	}

	Collision result = CheckCollision(*Ball, *Player);
	if (std::get<0>(result))
	{
		GLfloat centerPaddle = Player->Position.x + 0.5f * Player->Size.x;
		GLfloat distance = (Ball->Position.x + Ball->Radius) - centerPaddle;
		GLfloat percentage = distance / (Player->Size.x / 2);
		GLfloat strength = 5.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = 100 * percentage * strength;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
		Ball->Velocity.y = -abs(Ball->Velocity.y);
	}
	if (numCollidedBricks.size() > 3 || std::get<0>(result)) numCollidedBricks.clear();
}

Collision CheckCollision(BallObject &one, GameObject &two)
{
	glm::vec2 center(one.Position + one.Radius);
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	if (glm::length(difference) < one.Radius) return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] =
	{
		glm::vec2(0, 1),
		glm::vec2(1, 0),
		glm::vec2(-1, 0),
		glm::vec2(0, -1)
	};

	GLfloat max = -1;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; ++i)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	
	return (Direction)best_match;
}