#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Instruccions.h"
#include "Credits.h"
#include "Scene.h"
#include "Menu.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define TILE_SIZE 16


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();

	void changeMenu(int actual);
	void changeInstruccions();
	void changeCredits();
	void changeSceneActual(int actual);
	int getSceneActual() { return sceneActual; }

	void posPlayerScene(int posplayerX, int posplayerY);
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool getMouse() const;
	glm::ivec2 getMousePosition() const;

private:

	//Per tal de visualitzar el menu, les instruccions i els credits
	bool menu, instruccions, credits;
	bool bPlay, mouse;
	Scene scene[3];
	bool keys[256], specialKeys[256];
	glm::ivec2 mousePosition;

	int sceneActual;
};


#endif // _GAME_INCLUDE


