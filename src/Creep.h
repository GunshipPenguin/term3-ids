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
	Creep();
	Creep(int,int,double,std::string);
	void getFuturePosition(double timeDelta, float& x, float& y);
	void setFuturePosition(double timeDelta,float& x,float& y);
	float getXPosition();
	float getYPosition();
	bool isLeaked();
	void update();
	std::string getId();
	void draw(sf::RenderWindow&);
	static void setCreepPathfinder(CreepPathfinder&);
private:
	static CreepPathfinder paths_;
	int comingFrom_;
	int hp_;
	double speed_;//represented as a fraction of a tile per second
	std::string id_;
	bool leaked_;
};

#endif
