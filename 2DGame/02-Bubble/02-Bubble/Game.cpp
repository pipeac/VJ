#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include "Game.h"


void Game::init()
{
	bPlay = true;

	instruccions = false;
	credits = false;
	menu = true;
	
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	//Gumba_in & Tortuga_in son presents en la Scena
	Menu::instance().init();
	Instruccions::instance().init();
	Credits::instance().init();

	bool gumba1 = true;
	bool tortuga1 = false;
	glm::vec2 posGumba1 = { glm::vec2(160, 560) };
	glm::vec2 posTortuga1;
	scene[0].init("levels/mapa1.txt", "levels/pathmapa1.txt", gumba1, tortuga1, posGumba1, posTortuga1);

	bool gumba2 = false;
	bool tortuga2 = true;
	glm::vec2 posGumba2;
	glm::vec2 posTortuga2 = { glm::vec2(256, 336) };
	scene[1].init("levels/mapa2.txt", "levels/pathmapa2.txt", gumba2, tortuga2, posGumba2, posTortuga2);

	bool gumba3 = true;
	bool tortuga3 = true;
	glm::vec2 posGumba3 = { glm::vec2(160, 560) };
	glm::vec2 posTortuga3 = { glm::vec2(400, 543) };
	scene[2].init("levels/mapa3.txt", "levels/pathmapa3.txt", gumba3, tortuga3, posGumba3, posTortuga3);
}

bool Game::update(int deltaTime)
{
	if (menu)
		Menu::instance().update(deltaTime);
	else if (instruccions)
		Instruccions::instance().update(deltaTime);
	else if (credits)
		Credits::instance().update(deltaTime);
	else 
	{
		int sceneAnterior = sceneActual;

		scene[sceneActual].update(deltaTime);

		int posplayerY = scene[sceneActual].getPosPlayer().y;
		sceneActual += scene[sceneActual].playerPosActual();

		if (sceneAnterior < sceneActual)
			scene[sceneActual].initPlayerScene(0, posplayerY);
		else if (sceneAnterior > sceneActual)
			scene[sceneActual].initPlayerScene(SCREEN_WIDTH - TILE_SIZE, posplayerY);
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (menu)
		Menu::instance().render();
	else if (instruccions)
		Instruccions::instance().render();
	else if (credits)
		Credits::instance().render();
	else 
		scene[sceneActual].render();
}

void Game::changeMenu(int actual)
{
	changeSceneActual(actual);
	scene[sceneActual].initPlayerScene(64, 544);
	menu = !menu;
}

void Game::changeInstruccions()
{
	instruccions = !instruccions;
}

void Game::changeCredits()
{
	credits = !credits;
}

void Game::changeSceneActual(int actual)
{
	sceneActual = actual;
}

void Game::posPlayerScene(int posplayerX, int posplayerY)
{
	scene[sceneActual].initPlayerScene(posplayerX,posplayerY);
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button, int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
	mouse = true;
}

void Game::mouseRelease(int button)
{
	mouse = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::getMouse() const
{
	return mouse;
}

glm::ivec2 Game::getMousePosition() const
{
	return mousePosition;
}