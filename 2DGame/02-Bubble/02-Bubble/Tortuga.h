#ifndef _TORTUGA_INCLUDE
#define _TORTUGA_INCLUDE


#include "Sprite.h"
#include "EnemyPath.h"


// Tortuga is basically an enemy Sprite that represents the enemy. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Tortuga
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void death();

	//setters
	void setEnemyMap(EnemyPath *enemymap);
	void setPosition(const glm::vec2 &pos);
	void setChutada(bool b) {
		chutada = b;
	}

	//getters
	bool getCrouched() {
		return crouched;
	}

	glm::ivec2 getPos() const { return position; }

private:
	bool crouched, chutada, left;
	glm::ivec2 tileMapDispl, position;
	int startY;
	Texture spritesheet;
	Sprite *sprite;
	EnemyPath *enemypath;

};


#endif // _TORTUGA_INCLUDE
