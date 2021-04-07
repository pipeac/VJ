#include "Credits.h"



#include <iostream>
#include <cmath>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "Credits.h"



Credits::Credits()
{
}

Credits::~Credits()
{
}


void Credits::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 640.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	texs.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs.setMagFilter(GL_NEAREST);
	projection = glm::ortho(0.f, float(640 - 1), float(640 - 1), 0.f);

	currentTime = 0.0f;
}

void Credits::update(int deltaTime)
{
	if (Game::instance().getMouse())
	{
		if (88 <= Game::instance().getMousePosition().x && Game::instance().getMousePosition().x <= 394 &&
			556 <= Game::instance().getMousePosition().y && Game::instance().getMousePosition().y <= 597)
		{
			Game::instance().changeMenu(1);
			Game::instance().changeCredits();
		}

	}

	currentTime += deltaTime;
}

void Credits::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad->render(texs);
}

void Credits::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}