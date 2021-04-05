#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Gumba.h"
#include "Game.h"


#define FALL_STEP 4


enum EnemyAnims
{
	MOVE, DIE
};


void Gumba::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	die = false;
	size = glm::ivec2(16, 16);

	spritesheet.loadFromFile("images/SpritesGumba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(MOVE, 2);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.5f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));

}

void Gumba::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (die) 
		sprite->changeAnimation(DIE);
	else //el gumba se encuentra vivo
	{
		if (left)
			position.x -= 2;
		else //if (right)
			position.x += 2;

		if (enemypath->collisionMoveLeft(position, size))
			left = false;
		else if (enemypath->collisionMoveRight(position, size))
			left = true;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void Gumba::render()
{
	sprite->render();
}

void Gumba::setEnemyMap(EnemyPath *enemymap)
{
	enemypath = enemymap;
}

void Gumba::death()
{
	die = true;
}

void Gumba::setPosition(const glm::vec2 &pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}