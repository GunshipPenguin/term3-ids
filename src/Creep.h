#ifndef CREEP_H
#define CREEP_H

#include "Updateable.h"
#include "Tile.h"
#include <vector>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "CreepPathfinder.h"
#include "TileDrawable.h"

class Creep: public Updateable, public TileDrawable {
public:
	Creep();
	Creep(int,int,double,std::string);
	sf::Vector2f getFuturePosition(double timeDelta);
	float getXPosition();
	float getYPosition();
	bool isLeaked();
	void update();
	std::string getId();
	void draw(sf::RenderWindow&);
	static void setCreepPathfinder(CreepPathfinder&);
private:
	bool isAbove(int,int);
	bool isBelow(int,int);
	bool isLeft(int,int);
	bool isRight(int,int);
	static CreepPathfinder paths_;
	int comingFrom_;
	int hp_;
	double speed_;//represented as a fraction of a tile per second
	std::string id_;
	bool leaked_;
};

#endif
