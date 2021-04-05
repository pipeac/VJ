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
	//Inicialitzacio obligatoria feta per la constructora
	map = NULL;
	enemymap = NULL;
	gumba = NULL;
	tortuga = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (enemymap != NULL)
		delete enemymap;
	if (gumba != NULL)
		delete gumba;
	if (tortuga != NULL)
		delete tortuga;
}


void Scene::init(string loadmap, string loadenemypath, bool bGumba_in, bool bTortuga_in)
{
	initShaders();

	//variables iniciales del Mario
	Mario_chocado = false;
	Mario_death = false;
	Mario_visible = true;
	Gumba_in = bGumba_in;
	Tortuga_in = bTortuga_in;
	Gumba_tmp_moribundo = 0;
	Mario_tmp_inmune = 0;

	//variables a reusar de los enemigos
	
	tortuga_size = glm::ivec2(16, 24);

	map = TileMap::createTileMap(loadmap, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	enemymap = EnemyPath::createEnemyPath(loadenemypath, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	Player::instance().init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	if (Gumba_in)
	{
		gumba = new Gumba();
		gumba->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		gumba->setPosition(glm::vec2(INIT_ENEMY_X_TILES * enemymap->getTileSize(), INIT_ENEMY_Y_TILES * enemymap->getTileSize()));
		gumba->setEnemyMap(enemymap);
		gumba_size = gumba->getSize();
	}
	
	
	if (Tortuga_in) 
	{
		tortuga = new Tortuga();
		tortuga->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		tortuga->setPosition(glm::vec2(INIT_TORTUGA_X_TILES * enemymap->getTileSize(), INIT_TORTUGA_Y_TILES * enemymap->getTileSize()));
		tortuga->setEnemyMap(enemymap);
	}


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	int MarioAntPos_Y = Player::instance().getPosPlayer().y;
	
	if (Gumba_in)  gumba->update(deltaTime); 
	if (Tortuga_in) tortuga->update(deltaTime);
	Player::instance().update(deltaTime);

	glm::ivec2 posp = Player::instance().getPosPlayer();
	int height = Player::instance().getCrouchPlayer();
	glm::ivec2 pose(0);
	if (Gumba_in)	pose = gumba->getPos();
	glm::ivec2 postortuga;
	if (tortuga != NULL) postortuga = tortuga->getPosEnemy();


	//colision con el gumba
	if (!Mario_chocado && map->pain(posp, glm::ivec2(16, 32), pose, gumba_size))
	{
		if (map->death(MarioAntPos_Y + 31, posp.y + 31, pose.y, gumba_size))
		{
			if (Gumba_in)
			{
				gumba->death();
				gumba_size.y = 0;
			}
		}
		else if (!Mario_death)
		{
			Mario_death = Player::instance().death();
			if (!Mario_death)
			{
				Mario_chocado = true;
				auxchocar = 0.0f;
				Mario_tmp_inmune = 0;
			}
		}
	}

	//colision con la tortuga
	if (!Mario_chocado && map->pain(posp, glm::ivec2(16, 32), postortuga, tortuga_size))
	{
		if (map->death(MarioAntPos_Y + 31, posp.y + 31, postortuga.y, tortuga_size))
		{
			if (tortuga != NULL)
			{
				tortuga->death();
				Player::instance().set_Jumping(true);
				tortuga_size.y = 16;
				
			}
		}
		else if (!Mario_death)
		{
			Mario_death = Player::instance().death();
			if (!Mario_death)
			{
				Mario_chocado = true;
				auxchocar = 0.0f;
				Mario_tmp_inmune = 0;
			}
		}
	}

	if (Mario_chocado && map->pain(posp, glm::ivec2(16, 32), postortuga, tortuga_size)) {
		if (tortuga != NULL) {
			if (tortuga->getCrouched()) {
				tortuga->setChutada(true);
			}
		}
	}

	


	if (Mario_chocado)
	{
		if (auxchocar >= 60.0f) 
		{
			Mario_visible = !Mario_visible;
			if (Mario_tmp_inmune == 20) //ya hemos sobrepasado el tiempo de inmunidad
			{
				Mario_chocado = false;
				Mario_visible = true;
			}
			Mario_tmp_inmune++;
			auxchocar = 0.0f;
		}
		auxchocar += deltaTime;
	}


	//Finalmente, actualizamos



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
	if (Tortuga_in) tortuga->render();
	if (Mario_visible)
		Player::instance().render();
	if (Gumba_in) {
		if (Gumba_tmp_moribundo != 30)
		{
			gumba->render();
			if (gumba_size.y == 0) {
				Gumba_tmp_moribundo++;
			}
		}
	}
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
	if (posPlayer.x >= 624) //El Mario ha traspassat l'escena i per tant, caldrà actualizar a la nova escena //Esta avançant cap la dreta
		return 1;
	else if (posPlayer.x <= 0) //El Mario ha traspassat l'escena i per tant, caldrà actualizar a la nova escena //Retrocedeix cap a l'esquerra
		return -1;
	else
		return 0; //El Mario es troba en la mateixa escena i no cal actualitzar escena
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