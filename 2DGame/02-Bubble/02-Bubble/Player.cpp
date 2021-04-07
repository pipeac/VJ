#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cassert>
#include <cmath>
#include <map>

#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, VINE_LEFT, VINE_RIGHT, VINE_STAND_LEFT, VINE_STAND_RIGHT, JUMP_LEFT, JUMP_RIGHT, DIE, CROUCH, PIPEDOWN, PIPEUP
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	//inicialitzar hash map power ups
	powerups["Bolet"] = false;
	powerups["Estrella"] = false;
	powerups["Diners"] = false;
	powerups["Rellotge"] = false;
	powerups["Botes"] = false;

	canviEscenaPipe = false;
	MarioPipe = false;
	bJumping = false;
	auxJump = true;
	vine = false;
	size_crouched = 0;
	life = 10;
	exp = 0;
	spritesheet.loadFromFile("images/SpritesMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.2, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);

	
		sprite->setAnimationSpeed(STAND_LEFT, 0);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 0);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.75f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.75f));

		sprite->setAnimationSpeed(VINE_LEFT, 4);
		sprite->addKeyframe(VINE_LEFT, glm::vec2(0.4f, 0.5f));
		sprite->addKeyframe(VINE_LEFT, glm::vec2(0.4f, 0.75f));

		sprite->setAnimationSpeed(VINE_RIGHT, 4);
		sprite->addKeyframe(VINE_RIGHT, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(VINE_RIGHT, glm::vec2(0.6f, 0.75f));

		sprite->setAnimationSpeed(VINE_STAND_LEFT, 0);
		sprite->addKeyframe(VINE_STAND_LEFT, glm::vec2(0.4f, 0.5f));

		sprite->setAnimationSpeed(VINE_STAND_RIGHT, 0);
		sprite->addKeyframe(VINE_STAND_RIGHT, glm::vec2(0.6f, 0.5f));

		sprite->setAnimationSpeed(JUMP_LEFT, 0);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.4f, 0.25f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 0);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.4f, 0.f));

		sprite->setAnimationSpeed(DIE, 0);
		sprite->addKeyframe(DIE, glm::vec2(0.6f, 0.f));

		sprite->setAnimationSpeed(CROUCH, 0);
		sprite->addKeyframe(CROUCH, glm::vec2(0.6f, 0.25f));

		sprite->setAnimationSpeed(PIPEDOWN, 3);
		sprite->addKeyframe(PIPEDOWN, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(PIPEDOWN, glm::vec2(0.8f, 0.f));
		sprite->addKeyframe(PIPEDOWN, glm::vec2(0.8f, 0.25f));
		sprite->addKeyframe(PIPEDOWN, glm::vec2(0.8f, 0.5f));
		sprite->addKeyframe(PIPEDOWN, glm::vec2(0.8f, 0.75f));

		sprite->setAnimationSpeed(PIPEUP, 3);
		sprite->addKeyframe(PIPEUP, glm::vec2(0.8f, 0.75f));
		sprite->addKeyframe(PIPEUP, glm::vec2(0.8f, 0.5f));
		sprite->addKeyframe(PIPEUP, glm::vec2(0.8f, 0.25f));
		sprite->addKeyframe(PIPEUP, glm::vec2(0.8f, 0.f));
		sprite->addKeyframe(PIPEUP, glm::vec2(0.2f, 0.f));
		
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (MarioPipe) 
	{
		timeCanviEscenaPipe += deltaTime;
		if (!canviEscenaPipe && timeCanviEscenaPipe > 1600.f)
		{
			timeCanviEscenaPipe = 0;
			canviEscenaPipe = true;
			if (Game::instance().getSceneActual() == 1)
			{
				Game::instance().changeSceneActual(2);
				posPlayer = glm::ivec2(72, 544);
			}
			else if (Game::instance().getSceneActual() == 2)
			{
				Game::instance().changeSceneActual(1);
				posPlayer = glm::ivec2(552, 544);
			}
		}
		else if (canviEscenaPipe)
		{
			if (sprite->animation() != PIPEUP)
				sprite->changeAnimation(PIPEUP);
			if (timeCanviEscenaPipe > 1600.f)
			{
				MarioPipe = false;
				canviEscenaPipe = false;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
	}

	else 
	{
		if (life == 0 || map->collisionWater(posPlayer, glm::ivec2(16, 32), &posPlayer.y))
		{
			if (bJumping)
			{
				jumpAngle += JUMP_ANGLE_STEP;
				if (jumpAngle >= 180)
					posPlayer.y += FALL_STEP;
				else
					posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			}

			else
			{
				if (sprite->animation() != DIE)
				{
					sprite->changeAnimation(DIE);
					bJumping = true;
					life = 0;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}

		else
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))																			//Moure esquerra
			{
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 32)))
				{
					posPlayer.x += 2;
					sprite->changeAnimation(STAND_LEFT);

				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))																		//Moure dreta
			{
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 32)))
				{
					posPlayer.x -= 2;
					sprite->changeAnimation(STAND_RIGHT);
				}
			}
			else																														//Quedar-se quiet
			{
				if (sprite->animation() == MOVE_LEFT) 
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == MOVE_RIGHT) 
					sprite->changeAnimation(STAND_RIGHT);
			}

			if (map->VineMove(posPlayer, glm::ivec2(16, 32), &posPlayer.y))																//Pujar liana
			{
				vine = true;
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT || sprite->animation() == VINE_STAND_LEFT || sprite->animation() == JUMP_LEFT)
						sprite->changeAnimation(VINE_LEFT);
					else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT || sprite->animation() == VINE_STAND_RIGHT || sprite->animation() == JUMP_RIGHT)
						sprite->changeAnimation(VINE_RIGHT);
					posPlayer.y -= 1;
					auxJump = false;
				}
				else  if (!Game::instance().getSpecialKey(GLUT_KEY_DOWN))
				{
					if (sprite->animation() == VINE_RIGHT || sprite->animation() == JUMP_RIGHT) 
						sprite->changeAnimation(VINE_STAND_RIGHT);
					else if (sprite->animation() == VINE_LEFT || sprite->animation() == JUMP_LEFT) 
						sprite->changeAnimation(VINE_STAND_LEFT);
				}
			}

			else
			{
				if (!auxJump)
				{
					if (sprite->animation() == VINE_RIGHT) 
						sprite->changeAnimation(STAND_RIGHT);
					else if (sprite->animation() == VINE_LEFT) 
						sprite->changeAnimation(STAND_LEFT);
				}
				if (!Game::instance().getSpecialKey(GLUT_KEY_UP))
					auxJump = true;
				vine = false;
			}

			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))																			//Baixar liana
			{
				posPlayer.y += 1;
				if (map->VineMove(posPlayer, glm::ivec2(16, 32), &posPlayer.y)) {
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT || sprite->animation() == VINE_STAND_LEFT || sprite->animation() == JUMP_LEFT)
						sprite->changeAnimation(VINE_LEFT);
					else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT || sprite->animation() == VINE_STAND_RIGHT || sprite->animation() == JUMP_RIGHT)
						sprite->changeAnimation(VINE_RIGHT);
				}
				if (map->collisionMoveDownVine(posPlayer, glm::ivec2(16, 32), &posPlayer.y))
				{
					if (sprite->animation() != CROUCH)
						sprite->changeAnimation(CROUCH);
					size_crouched = 16;
					posPlayer.y -= 1;
				}
				if (!map->MoveDownPipe(posPlayer, glm::ivec2(16, 32), &posPlayer.x))
				{
					posPlayer.y -= 1;
					sprite->changeAnimation(PIPEDOWN);
					MarioPipe = true;
					timeCanviEscenaPipe = 0.f;
				}
			}

			else
			{
				size_crouched = 0;
				if (sprite->animation() == CROUCH)
					sprite->changeAnimation(STAND_RIGHT);
			}

			if (bJumping)																												//Saltar
			{
				jumpAngle += JUMP_ANGLE_STEP;
				if (jumpAngle == 180)
				{
					if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
					else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);

					bJumping = false;
					posPlayer.y = startY;
				}
				else
				{
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) sprite->changeAnimation(JUMP_LEFT);
					else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
					else sprite->changeAnimation(JUMP_RIGHT);

					posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
					if (jumpAngle > 90)
						bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 32), &posPlayer.y);
				}
			}

			else if (!vine)																												//Caure
			{
				posPlayer.y += FALL_STEP;
				if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 32), &posPlayer.y))
				{
					if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
					else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);

					if (Game::instance().getSpecialKey(GLUT_KEY_UP) && auxJump)
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

bool Player::death()
{
	life--;
	if (life == 0) return true;
	return false;
}

void Player::changePowerUp(string powerup)
{
	powerups[powerup] = !powerups[powerup];
}

void Player::setExpPlayer(int xp)
{
	exp += xp;
	if (exp == 48)
	{
		exp %= 48;
		if (life < 10)
			++life;
	}
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	if (!canviEscenaPipe)
		posPlayer = pos;
}