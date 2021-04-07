#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Texture.h"
#include "Text.h"
#include "Game.h"



class Credits
{

public:
	static Credits &instance()
	{
		static Credits C;

		return C;
	}
	Credits();
	~Credits();

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


#endif // _CREDITS_INCLUDE

