#include "Menu.h"



#include <iostream>
#include <cmath>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"



	Menu::Menu()
	{
	}

	Menu::~Menu()
	{
	}


	void Menu::init()
	{
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 640.f) };
		glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

		initShaders();
		texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
		texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

		texs.loadFromFile("images/MenuPrincipal.png", TEXTURE_PIXEL_FORMAT_RGBA);
		texs.setMagFilter(GL_NEAREST);
		projection = glm::ortho(0.f, float(640 - 1), float(640 - 1), 0.f);

		currentTime = 0.0f;
	}

	void Menu::update(int deltaTime)
	{
		if (Game::instance().getMouse())
		{
			if (195 <= Game::instance().getMousePosition().x && Game::instance().getMousePosition().x <= 445)
			{
				if (103 <= Game::instance().getMousePosition().y && Game::instance().getMousePosition().y <= 178)
					Game::instance().changeMenu(0);
				else if (281 <= Game::instance().getMousePosition().y && Game::instance().getMousePosition().y <= 356)
				{
					Game::instance().changeMenu(0);
					Game::instance().changeInstruccions();
				}
				else if (459 <= Game::instance().getMousePosition().y && Game::instance().getMousePosition().y <= 534)
				{
					Game::instance().changeMenu(0);
					Game::instance().changeCredits();
				}
			}
		}

		currentTime += deltaTime;
	}

	void Menu::render()
	{
		glm::mat4 modelview;

		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

		texProgram.setUniformMatrix4f("modelview", modelview);
		texQuad->render(texs);
	}

	void Menu::initShaders()
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