#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Tile : public Drawable {
public:
	void setId(int);
	int getId();
	void setCreepExit(bool);
	void setCreepSpawn(bool);
	void setCreepWalkable(bool);
	void setBuilt(bool);
	void setBuildable(bool);
	void setSprite(sf::Sprite);
	bool isCreepExit();
	bool isCreepSpawn();
	bool isCreepWalkable();
	bool isBuildable();
	bool isBuilt();
	void draw(sf::RenderWindow&, sf::Texture &tiles);

private:
	int id_;
	bool creepSpawn_;
	bool creepExit_;
	bool buildable_;
	bool creepWalkable_;
	bool built_;
};

#endif
