#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "EnemyPath.h"
#include "Player.h"
#include "Enemy.h"
#include "Tortuga.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(bool enemy1_in, bool enemy2_in);
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	int aux, auxTime;
	bool chocar, auxrender, death;
	TileMap *map;
	EnemyPath *enemymap;
	Player *player;
	Enemy *enemy;
	Tortuga *tortuga;
	ShaderProgram texProgram;
	float currentTime, auxchocar;
	glm::mat4 projection;
	glm::ivec2 gumba_size;
	glm::ivec2 tortuga_size;


};


#endif // _SCENE_INCLUDE

