#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "EnemyPath.h"


// Enemy is basically a Sprite that represents the enemy. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void death();

	void setEnemyMap(EnemyPath *enemymap);
	void setPosition(const glm::vec2 &pos);

	glm::ivec2 getPosEnemy() const { return posEnemy; }

private:
	bool die, left;
	glm::ivec2 tileMapDispl, posEnemy;
	int startY;
	Texture spritesheet;
	Sprite *sprite;
	EnemyPath *enemypath;

};


#endif // _ENEMY_INCLUDE
