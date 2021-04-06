#ifndef _DINERS_INCLUDE
#define _DINERS_INCLUDE


#include "Sprite.h"
#include "Texture.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Diners
{

public:

	void init(ShaderProgram &shaderProgram, const glm::vec2 &pos);
	void update(int deltaTime, bool diners);
	void render();

private:
	Texture spritesheet;
	Sprite *sprite;
};


#endif // _DINERS_INCLUDE


