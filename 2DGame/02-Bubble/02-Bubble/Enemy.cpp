#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


#define FALL_STEP 4


enum EnemyAnims
{
	MOVE, DIE
};


void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	die = false;
	spritesheet.loadFromFile("images/SpritesGumba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(MOVE, 2);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.5f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (die) 
		sprite->changeAnimation(DIE);
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


void Enemy::render()
{
	sprite->render();
}

void Enemy::setEnemyMap(EnemyPath *enemymap)
{
	enemypath = enemymap;
}

void Enemy::death()
{
	die = true;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}