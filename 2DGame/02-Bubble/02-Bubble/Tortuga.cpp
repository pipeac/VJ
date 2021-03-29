#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Tortuga.h"
#include "Game.h"


#define FALL_STEP 4


enum TortugaAnims
{
	MOVE, CROUCHED
};


void Tortuga::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	crouched = false;
	spritesheet.loadFromFile("images/SpritesTortuga.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(MOVE, 2);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(CROUCHED, 0);
	sprite->addKeyframe(CROUCHED, glm::vec2(0.5f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Tortuga::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (crouched)
		sprite->changeAnimation(CROUCHED);
	else
	{
		if (left)
			posEnemy.x -= 2;
		else
			posEnemy.x += 2;
		if (enemypath->collisionMoveLeft(posEnemy, glm::ivec2(16, 16)))
			left = false;
		else if (enemypath->collisionMoveRight(posEnemy, glm::ivec2(16, 16)))
			left = true;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
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
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}