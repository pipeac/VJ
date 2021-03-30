#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 27

#define INIT_ENEMY_X_TILES 10
#define INIT_ENEMY_Y_TILES 28

#define INIT_TORTUGA_X_TILES 9
#define INIT_TORTUGA_Y_TILES 27


Scene::Scene()
{
	map = NULL;
	enemymap = NULL;
	player = NULL;
	enemy = NULL;
	tortuga = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (enemymap != NULL)
		delete enemymap;
	if(player != NULL)
		delete player;

}


void Scene::init(bool enemy1_in, bool enemy2_in)
{
	initShaders();
	chocar = false;
	death = false;
	auxrender = true;
	gumba_size = glm::ivec2(16, 16);
	tortuga_size = glm::ivec2(16, 32);
	map = TileMap::createTileMap("levels/MapaProva.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	enemymap = EnemyPath::createEnemyPath("levels/EnemyPath.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

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
	int posant = player->getPosPlayer().y;
	player->update(deltaTime);
	if (enemy != NULL) enemy->update(deltaTime);
	if (tortuga != NULL) tortuga->update(deltaTime);

	glm::ivec2 posp = player->getPosPlayer();
	int height = player->getCrouchPlayer();
	glm::ivec2 pose(0);
	if (enemy != NULL)	pose = enemy->getPosEnemy();
	glm::ivec2 postortuga = tortuga->getPosEnemy();
	if (tortuga != NULL) postortuga = tortuga->getPosEnemy();

	if (!chocar && map->pain(posp, glm::ivec2(16, 32), pose, gumba_size))
	{
		if (map->death(posant + 31, posp.y + 31, pose.y, gumba_size))
		{
			if (enemy != NULL) enemy->death();
			if (enemy != NULL) gumba_size.y = 0;
		}
		else if (!death)
		{
			death = player->death();
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
			if (enemy != NULL) tortuga->death();
			if (enemy != NULL) tortuga_size.y = 0;
		}
		else if (!death)
		{
			death = player->death();
			if (!death)
			{
				chocar = true;
				auxchocar = 0.0f;
				aux = 0;
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
		player->render();
	if (auxTime != 30)
	{
		if (enemy != NULL) enemy->render();
		if (tortuga != NULL) tortuga->render();
		if (enemy != NULL && gumba_size.y == 0)
			auxTime++;
	}
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



