#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "TileSet.h"

class Drawable {
public:
	virtual void draw(sf::RenderWindow&) = 0;
	void setPosition(int, int);
	void setTileSet(TileSet*);

protected:
	TileSet* tileSet_;
	float x_;
	float y_;

};

#endif
