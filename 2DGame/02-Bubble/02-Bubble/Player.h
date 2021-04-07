#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include <map>

#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	static Player &instance()
	{
		static Player P;

		return P;
	}

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	bool death();
	
	void changePowerUp(string powerup);
	void setExpPlayer(int xp);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void set_Jumping(bool b) {
		bJumping = b;
		jumpAngle = 0;
		startY = posPlayer.y;
	}
	

	glm::ivec2 getPosPlayer() const { return posPlayer; }
	int getCrouchPlayer() const { return size_crouched; }
	int getLifePlayer() const { return life; }
	int getExpPlayer() const { return exp;  }
	
private:
	bool bJumping, vine, auxJump, MarioPipe, canviEscenaPipe;
	glm::ivec2 tileMapDispl, posPlayer, auxPosPlayer;
	int jumpAngle, startY, life, size_crouched, exp;
	std::map<std::string, bool> powerups;
	float timeCanviEscenaPipe;

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


