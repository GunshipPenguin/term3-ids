#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "TileSet.h"

class Tile : public Drawable {
public:
	void setId(int);
	void setCreepExit(bool);
	void setCreepSpawn(bool);
	void setCreepWalkable(bool);
	void setBuilt(bool);
	void setBuildable(bool);
	void setSprite(sf::Sprite);
	int getId() const;
	bool isCreepExit() const ;
	bool isCreepSpawn() const;
	bool isCreepWalkable() const;
	bool isBuildable() const;
	bool isBuilt() const;
	void draw(sf::RenderWindow&);

private:
	int id_;
	bool creepSpawn_;
	bool creepExit_;
	bool buildable_;
	bool creepWalkable_;
	bool built_;
};

#endif
