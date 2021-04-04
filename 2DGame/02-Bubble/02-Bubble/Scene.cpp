#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 34

#define INIT_ENEMY_X_TILES 10
#define INIT_ENEMY_Y_TILES 35

#define INIT_TORTUGA_X_TILES 9
#define INIT_TORTUGA_Y_TILES 34


Scene::Scene()
{
	map = NULL;
	enemymap = NULL;
	enemy = NULL;
	tortuga = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (enemymap != NULL)
		delete enemymap;
	if (enemy != NULL)
		delete enemy;
	if (tortuga != NULL)
		delete tortuga;
}


void Scene::init(string loadmap, string loadenemypath, bool enemy1_in, bool enemy2_in)
{
	initShaders();
	chocar = false;
	death = false;
	auxrender = true;
	gumba_size = glm::ivec2(16, 16);
	tortuga_size = glm::ivec2(16, 24);
	map = TileMap::createTileMap(loadmap, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	enemymap = EnemyPath::createEnemyPath(loadenemypath, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	Player::instance().init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	if (enemy2_in)
	{
		enemy = new Enemy();
		enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * enemymap->getTileSize(), INIT_ENEMY_Y_TILES * enemymap->getTileSize()));
		enemy->setEnemyMap(enemymap);
	}
	
	
	if (enemy1_in) 
	{
		tortuga = new Tortuga();
		tortuga->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		tortuga->setPosition(glm::vec2(INIT_TORTUGA_X_TILES * enemymap->getTileSize(), INIT_TORTUGA_Y_TILES * enemymap->getTileSize()));
		tortuga->setEnemyMap(enemymap);
	}

	

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	auxTime = 0;
	aux = 0;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	int posant = Player::instance().getPosPlayer().y;
	Player::instance().update(deltaTime);
	if (enemy != NULL) enemy->update(deltaTime);
	if (tortuga != NULL) tortuga->update(deltaTime);

	glm::ivec2 posp = Player::instance().getPosPlayer();
	int height = Player::instance().getCrouchPlayer();
	glm::ivec2 pose(0);
	if (enemy != NULL)	pose = enemy->getPosEnemy();
	glm::ivec2 postortuga;
	if (tortuga != NULL) postortuga = tortuga->getPosEnemy();

	if (!chocar && map->pain(posp, glm::ivec2(16, 32), pose, gumba_size))
	{
		if (map->death(posant + 31, posp.y + 31, pose.y, gumba_size))
		{
			if (enemy != NULL)
			{
				enemy->death();
				gumba_size.y = 0;
			}
		}
		else if (!death)
		{
			death = Player::instance().death();
			if (!death)
			{
				chocar = true;
				auxchocar = 0.0f;
				aux = 0;
			}
		}
	}

	
	if (!chocar && map->pain(posp, glm::ivec2(16, 32), postortuga, tortuga_size))
	{
		if (map->death(posant + 31, posp.y + 31, postortuga.y, tortuga_size))
		{
			if (tortuga != NULL)
			{
				tortuga->death();
				tortuga_size.y = 16;
			}
		}
		else if (!death)
		{
			death = Player::instance().death();
			if (!death)
			{
				chocar = true;
				auxchocar = 0.0f;
				aux = 0;
			}
		}
	}

	if (chocar && map->pain(posp, glm::ivec2(16, 32), postortuga, tortuga_size)) {
		if (tortuga != NULL) {
			if (tortuga->getCrouched()) {
				tortuga->setChutada(true);
			}
		}
	}

	


	if (chocar)
	{
		if (auxchocar >= 60.0f) 
		{
			auxrender = !auxrender;
			if (aux == 20) 
			{
				chocar = false;
				auxrender = true;
			}
			aux++;
			auxchocar = 0.0f;
		}
		auxchocar += deltaTime;
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	if (auxrender)
		Player::instance().render();
	if (auxTime != 30)
	{
		if (enemy != NULL) enemy->render();
		if (enemy != NULL && gumba_size.y == 0)
			auxTime++;
	}
	if (tortuga != NULL) tortuga->render();
}

void Scene::initPlayerScene(int posplayerX, int posplayerY)
{
	Player::instance().setPosition(glm::vec2(posplayerX, posplayerY));
	Player::instance().setTileMap(map);
}

glm::vec2 Scene::getPosPlayer()
{
	return Player::instance().getPosPlayer();
}

int Scene::playerPosActual()
{
	glm::ivec2 posPlayer = getPosPlayer();
	if (posPlayer.x >= 624)
		return 1;
	else if (posPlayer.x <= 0)
		return -1;
	else
		return 0;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}