#ifndef _BOLET_INCLUDE
#define _BOLET_INCLUDE


#include "Sprite.h"
#include "Texture.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Bolet
{

public:

	void init(ShaderProgram &shaderProgram, const glm::vec2 &pos);
	void render();
	void setPosition(const glm::vec2 &pos);

private:
	Texture spritesheet;
	Sprite *sprite;
};


#endif // _BOLET_INCLUDE


