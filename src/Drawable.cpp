#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Drawable::setPosition(int xPosition, int yPosition) {
	x_ = xPosition;
	y_ = yPosition;
	return;
}

void Drawable::setTileSet(TileSet* tileSet) {
	tileSet_ = tileSet;
	return;
}
