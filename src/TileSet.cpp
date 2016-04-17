#include "TileSet.h"
#include <string>

void TileSet::setTileSize(int tileSize) {
	tileSize_ = tileSize;
	return;
}

int TileSet::getTileSize() {
	return tileSize_;
}

void TileSet::loadTextureFromFile(std::string path) {
	texture_.loadFromFile(path);
	return;
}
