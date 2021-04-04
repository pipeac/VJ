#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene[0].init("levels/mapa1.txt", "levels/pathmapa1.txt", 1, 0);
	scene[0].initPlayerScene(64, 544);
	scene[1].init("levels/mapa2.txt", "levels/pathmapa2.txt", 0, 1);
}

bool Game::update(int deltaTime)
{
	int sceneAnterior = sceneActual;

	scene[sceneActual].update(deltaTime);

	int posplayerY = scene[sceneActual].getPosPlayer().y;
	sceneActual += scene[sceneActual].playerPosActual();

	if (sceneAnterior < sceneActual)
		scene[sceneActual].initPlayerScene(0, posplayerY);
	else if (sceneAnterior > sceneActual)
		scene[sceneActual].initPlayerScene(SCREEN_WIDTH - TILE_SIZE, posplayerY);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene[sceneActual].render();
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

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





