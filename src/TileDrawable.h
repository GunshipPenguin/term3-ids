#ifndef TILEDRAWABLE_H
#define TILEDRAWABLE_H

#include "TileSet.h"
#include "Drawable.h"

#include <SFML/Graphics.hpp>

class TileDrawable : public Drawable {
public:
	virtual void draw(sf::RenderWindow&) = 0;
	void setTileSet(TileSet*);

protected:
	TileSet* tileSet_;

};

#endif
