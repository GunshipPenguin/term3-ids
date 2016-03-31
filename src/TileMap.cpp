#include "TileMap.h"
#include <string>

Tile TileMap::getTile(int x, int y) {
	return tiles_.at(y).at(x);
}

void TileMap::setTile(int x, int y, Tile tile) {
	tiles_.at(x).at(y) = tile;
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

int TileMap::getYDimen() {
	return yDimen_;
}
