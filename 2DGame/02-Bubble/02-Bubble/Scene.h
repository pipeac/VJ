#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "EnemyPath.h"
#include "Player.h"
#include "Gumba.h"
#include "Tortuga.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(string loadmap, string loadenemypath, bool Tortuga_in, bool Gumba_in);
	void update(int deltaTime);
	void render();
	void initPlayerScene(int posplayerX, int posplayerY);

	glm::vec2 getPosPlayer();

	int playerPosActual();

private:
	void initShaders();

private:
	int Mario_tmp_inmune, Gumba_tmp_moribundo;
	
	//Indicador sobre el Mario se encuentra en estado chocado, lo que implica que no sufre daño adicional
	bool Mario_chocado;
	//Indicador sobre si el Mario se puede renderizar
	bool Mario_visible;
	//Indicador sobre el Mario se encuentra en estado muerto, lo que implica activar la animación de DIE
	bool Mario_death;

	bool canviescena;
	TileMap *map;
	EnemyPath *enemymap;
	Gumba *gumba;
	Tortuga *tortuga;
	ShaderProgram texProgram;
	float currentTime, auxchocar;
	glm::mat4 projection;
	glm::ivec2 gumba_size;
	glm::ivec2 tortuga_size;

	bool Gumba_in, Tortuga_in;


};


#endif // _SCENE_INCLUDE

