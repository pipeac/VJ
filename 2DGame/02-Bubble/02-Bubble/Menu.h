#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Texture.h"
#include "Text.h"
#include "Game.h"


class Menu
{

public:
	static Menu &instance()
	{
		static Menu M;

		return M;
	}
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:

	float currentTime;
	glm::mat4 projection;

	ShaderProgram texProgram;
	TexturedQuad *texQuad;
	Texture texs;
	Text text;
};


#endif // _MENU_INCLUDE

