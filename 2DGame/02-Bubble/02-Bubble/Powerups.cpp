#include "Powerups.h"

#include <map>
#include <iostream>
#include <cassert>


enum PowerupsAnims
{
	BOLET, ESTRELLA, DINERS, RELLOTGE, BOTES
};


Powerups::Powerups()
{
	powerupsprites["Bolet"] = 0;
	powerupsprites["Estrella"] = 1;
	powerupsprites["Diners"] = 2;
	powerupsprites["Rellotge"] = 3;
	powerupsprites["Botes"] = 4;

	powerups["Bolet"] = false;
	powerups["Estrella"] = false;
	powerups["Diners"] = false;
	powerups["Rellotge"] = false;
	powerups["Botes"] = false;
}

Powerups::~Powerups()
{
	powerupsprites.erase("Bolet");
	powerupsprites.erase("Estrella");
	powerupsprites.erase("Diners");
	powerupsprites.erase("Rellotge");
	powerupsprites.erase("Botes");

	powerups.erase("Bolet");
	powerups.erase("Estrella");
	powerups.erase("Diners");
	powerups.erase("Rellotge");
	powerups.erase("Botes");
}

void Powerups::init(ShaderProgram &shaderProgram, const string powerup, const glm::vec2 &pos)
{
	powerups[powerup] = true;

	spritesheet.loadFromFile("images/PowerUps.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.2f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(BOLET, 0);
	sprite->addKeyframe(BOLET, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(ESTRELLA, 0);
	sprite->addKeyframe(ESTRELLA, glm::vec2(0.2f, 0.f));

	sprite->setAnimationSpeed(DINERS, 0);
	sprite->addKeyframe(DINERS, glm::vec2(0.4f, 0.f));

	sprite->setAnimationSpeed(RELLOTGE, 0);
	sprite->addKeyframe(RELLOTGE, glm::vec2(0.6f, 0.f));

	sprite->setAnimationSpeed(BOTES, 0);
	sprite->addKeyframe(BOTES, glm::vec2(0.8f, 0.f));

	sprite->changeAnimation(powerupsprites[powerup]);
	sprite->setPosition(pos);
}

void Powerups::render()
{
	sprite->render();
}

string Powerups::getPowerup()
{
	if (powerups["Bolet"])
		return "Bolet";
	else if (powerups["Estrella"])
		return "Estrella";
	else if (powerups["Diners"])
		return "Diners";
	else if (powerups["Rellotge"])
		return "Rellotge";
	else if (powerups["Botes"])
		return "Botes";
}
