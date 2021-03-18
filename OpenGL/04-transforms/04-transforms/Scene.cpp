#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	quad = NULL;
}

Scene::~Scene()
{
	if(quad != NULL)
		delete quad;
}


void Scene::init()
{
	initShaders();
	quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, program);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	glm::mat4 modelview;
	float value = (sin(currentTime / 1000.f) + 1.0f) / 2.0f;
	float value1 = (sin(currentTime / 1000.f) + 1.0f) / 2.6667f + 0.25f;
	cout << value1 << endl;

	// We can now, using matrices, draw four quads at different screen locations
	// using a single Quad object.
	program.use();
	program.setUniformMatrix4f("projection", projection);
	program.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(value * 192.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(value1, value1, 1.f));
	//modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	program.setUniformMatrix4f("modelview", modelview);
	quad->render();

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(512.f - value * 192.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(value1, value1, 1.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	program.setUniformMatrix4f("modelview", modelview);
	quad->render();

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(value * 192.f, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(value1, value1, 1.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	program.setUniformMatrix4f("modelview", modelview);
	quad->render();

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(512.f - value * 192.f, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(value1, value1, 1.f));
	//modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	program.setUniformMatrix4f("modelview", modelview);
	quad->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if(!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
}

