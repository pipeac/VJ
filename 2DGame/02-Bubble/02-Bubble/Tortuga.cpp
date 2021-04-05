#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Tortuga.h"
#include "Game.h"


#define FALL_STEP 4


enum TortugaAnims
{
	MOVE_LEFT, MOVE_RIGHT, CROUCHED_STAND, CROUCHED_MOVE
};


void Tortuga::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	crouched = false;
	left = true;
	spritesheet.loadFromFile("images/SpritesTortuga.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.5, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);


	sprite->setAnimationSpeed(MOVE_LEFT, 4);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 4);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(CROUCHED_STAND, 0);
	sprite->addKeyframe(CROUCHED_STAND, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(CROUCHED_MOVE, 0);
	sprite->addKeyframe(CROUCHED_STAND, glm::vec2(0.5f, 0.5f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));

}

void Tortuga::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (crouched) {
		sprite->changeAnimation(CROUCHED_STAND);
		if (chutada) {
			sprite->changeAnimation(CROUCHED_STAND);
			if (left) {
				position.x -= 3;
			}
			if (!left) { //if (right)
				position.x += 3;

			}
		}
	}
		

	else //la tortuga esta dempeus
	{
		if (left) 
		{
			position.x -= 2;
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
		}
		else //està en modo RIGHT
		{
			position.x += 2;
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
		}
		//if (enemypath->collisionMoveLeft(posEnemy, glm::ivec2(16, 32)))
		//	left = false; //acivem el modo RIGHT
		//else if (enemypath->collisionMoveRight(posEnemy, glm::ivec2(16, 32)))
		//	left = true; //activem el modo LEFT
	}
	if (enemypath->collisionMoveLeft(position, glm::ivec2(16, 16)))
		left = false; //acivem el modo RIGHT
	else if (enemypath->collisionMoveRight(position, glm::ivec2(16, 16)))
		left = true; //activem el modo LEFT

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void Tortuga::render()
{
	sprite->render();
}

void Tortuga::setEnemyMap(EnemyPath *enemymap)
{
	enemypath = enemymap;
}

void Tortuga::death()
{
	crouched = true;
}

void Tortuga::setPosition(const glm::vec2 &pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}
