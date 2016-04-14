#include "TileMap.h"
#include <string>

Tile TileMap::getTile(int x, int y) {
	return tiles_.at(y).at(x);
}

void TileMap::setTile(int x, int y, Tile tile) {
	tiles_.at(x).at(y) = tile;
	return;
}

void TileMap::setTexture(sf::Texture texture) {
    texture_ = texture;
    return;
}

int TileMap::getTileSize() {
	return tileSize_;
}

void TileMap::setTileSize(int tileSize) {
	tileSize_ = tileSize;
	return;
}

int TileMap::getXDimen() {
	return xDimen_;
}

void TileMap::setXDimen(int xDimen) {
    xDimen_ = xDimen;
    return;
}

void TileMap::setYDimen(int yDimen) {
    yDimen_ = yDimen;
    return;
}

int TileMap::getYDimen() {
	return yDimen_;
}
