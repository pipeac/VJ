#include "Bolet.h"


enum BoletAnims
{
	SHOW
};


void Bolet::init(ShaderProgram &shaderProgram, const glm::vec2 &pos)
{
	spritesheet.loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(SHOW, 0);
	sprite->addKeyframe(SHOW, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	sprite->setPosition(pos);

}

void Bolet::render()
{
	sprite->render();
}

void Bolet::setPosition(const glm::vec2 &pos)
{
	sprite->setPosition(pos);
}