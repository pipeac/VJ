#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "EnemyPath.h"


// Enemy is basically a Sprite that represents the enemy. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Gumba
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void death();

	//setters
	void setEnemyMap(EnemyPath *enemymap);
	void setPosition(const glm::vec2 &pos);
	void setSize(glm::ivec2 vec_size) {size = vec_size;}

	//getters
	glm::ivec2 getPos() const { return position; }
	glm::ivec2 getSize() const { return size; }

	
private:
	bool die, left;
	glm::ivec2 tileMapDispl, position;
	glm::ivec2 size;
	int startY;
	Texture spritesheet;
	Sprite *sprite;
	EnemyPath *enemypath;

};


#endif // _ENEMY_INCLUDE
