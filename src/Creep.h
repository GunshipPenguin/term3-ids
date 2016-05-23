#ifndef CREEP_H
#define CREEP_H

#include "Drawable.h"
#include "Path.h"
#include "Updateable.h"
#include "Tile.h"
#include <vector>
#include <cmath>
#include <iostream> // remove after testing
#include <SFML/Graphics.hpp>

class Creep: public Updateable, public Drawable {
public:
	Creep(int,int,int,double);
	int getPositionByTile();
	sf::Vector2f getPosition(bool);//boolean is for centered
	void setFuturePosition(double timeDelta,float& x,float& y);//boolean is for centered
	void update();
	void draw(sf::RenderWindow &window, sf::Texture &tiles);
	static void setPath(Path&);
private:
	static Path paths_;
	std::vector<int> path_;
	int pathPosition_;//updates when creep covers "next" tile
	double speed_;//represented as a fraction of a tile per second
	int tileSize_;
	int numTilesX_;
	sf::Vector2f coordinates_;
};

#endif
