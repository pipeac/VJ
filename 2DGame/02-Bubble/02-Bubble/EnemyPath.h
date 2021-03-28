#ifndef _ENEMY_PATH_INCLUDE
#define _ENEMY_PATH_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class EnemyPath is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class EnemyPath
{

public:
	// Tile maps can only be created inside an OpenGL context
	static EnemyPath *createEnemyPath(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	EnemyPath(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~EnemyPath();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;

};


#endif // _ENEMY_PATH_INCLUDE