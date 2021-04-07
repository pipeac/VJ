#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "EnemyPath.h"
#include "TileMap.h"
#include "Tortuga.h"
#include "Player.h"
#include "Diners.h"
#include "Gumba.h"
#include "Bolet.h"
#include "Text.h"
#include "Quad.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(string loadmap, string loadenemypath, bool Gumba_in, bool Tortuga_in, glm::vec2 posGumba, glm::vec2 posTortuga);
	void update(int deltaTime);
	void render();
	void initPlayerScene(int posplayerX, int posplayerY);

	void updateBolets(int deltaTime);
	void updateDiners(int deltaTime);

	glm::ivec2 getPosPlayer();

	int playerPosActual();

private:
	void initShaders();

private:
	int Mario_tmp_inmune, gumba_tmp_moribundo;
	
	//Indicador sobre el Mario se encuentra en estado chocado, lo que implica que no sufre daño adicional
	bool Mario_chocado;
	//Indicador sobre si el Mario se puede renderizar
	bool Mario_visible;
	//Indicador sobre el Mario se encuentra en estado muerto, lo que implica activar la animación de DIE
	bool Mario_death;

	bool canviescena;
	bool Gumba_in, Tortuga_in;
	float currentTime, auxchocar;

	EnemyPath *enemymap;
	Tortuga *tortuga;
	TileMap *map;
	Gumba *gumba;
	Quad *quad;

	ShaderProgram texProgram;
	Bolet bolet[10];
	Diners diners[100];
	Text text;

	glm::ivec2 tortuga_size;
	glm::ivec2 gumba_size;

	glm::mat4 projection;
};


#endif // _SCENE_INCLUDE

