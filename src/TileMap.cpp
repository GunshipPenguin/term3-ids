#include "TileMap.h"
#include <vector>

void TileMap::draw(sf::RenderWindow& window) {
	size_t i;
	for (i=0;i<tiles_.size();i++) {
		tiles_.at(i).draw(window);
	}
	return;
}

void TileMap::setTiles(std::vector<Tile>& tiles) {
	tiles_ = tiles;
	return;
}

void TileMap::setNumTilesX(int numTilesX) {
	numTilesX_ = numTilesX;
	return;
}

void TileMap::layoutTiles(int tileSize) {
	// Set tile positions
	sf::Vector2f position;
	int x, y;
	for (size_t i=0;i<tiles_.size();i++) {
		x = (i % numTilesX_) * TileSet::getDrawnSize();
		y = (i / numTilesX_) * TileSet::getDrawnSize();
		tiles_.at(i).setPosition(x, y);
	}
	return;
}

const std::vector<Tile>& TileMap::getTiles() const {
	return tiles_;
}

int TileMap::getNumTilesX() {
	return numTilesX_;
}

int TileMap::getNumTilesY() {
	return tiles_.size() / numTilesX_;
}
