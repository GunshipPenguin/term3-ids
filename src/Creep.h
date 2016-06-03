#ifndef CREEP_H
#define CREEP_H

#include "Drawable.h"
#include "Updateable.h"
#include "Tile.h"
#include <vector>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "CreepPathfinder.h"

class Creep: public Updateable, public Drawable {
public:
	Creep(int,int,int,double,std::string);
	int getPositionByTile();
	sf::Vector2f getPosition(bool);//boolean is for centered
	void setFuturePosition(double timeDelta,float& x,float& y);//boolean is for centered
	void update();
	std::string getId();
	void draw(sf::RenderWindow&);
	static void setCreepPathfinder(CreepPathfinder&);
private:
	static CreepPathfinder paths_;
	std::string id_;
	std::vector<int> path_;
	int pathPosition_;//updates when creep covers "next" tile
	double speed_;//represented as a fraction of a tile per second
	int tileSize_;
	int numTilesX_;
	sf::Vector2f coordinates_;
};

#endif
