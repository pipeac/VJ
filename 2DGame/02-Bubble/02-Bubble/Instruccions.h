#ifndef _INSTRUCCIONS_INCLUDE
#define _INSTRUCCIONS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Texture.h"
#include "Text.h"
#include "Game.h"



class Instruccions
{

public:
	static Instruccions &instance()
	{
		static Instruccions I;

		return I;
	}
	Instruccions();
	~Instruccions();

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


#endif // _INSTRUCCIONS_INCLUDE

