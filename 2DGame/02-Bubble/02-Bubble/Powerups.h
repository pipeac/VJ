#ifndef _POWERUPS_INCLUDE
#define _POWERUPS_INCLUDE

#include <map>

#include "Sprite.h"
#include "Texture.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Powerups
{

public:
	Powerups();
	~Powerups();

	void init(ShaderProgram &shaderProgram, const string powerup, const glm::vec2 &pos);
	void render();

	string getPowerup();

private:
	Texture spritesheet;
	Sprite *sprite;

	std::map<std::string, int> powerupsprites;
	std::map<std::string, int> powerups;
};


#endif // _POWERUPS_INCLUDE


