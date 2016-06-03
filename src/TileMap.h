#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class TileMap: public Drawable {
public:
	TileMap() :
		tiles_(std::vector<Tile>()),
		numTilesX_(1) {};
	TileMap(std::vector<Tile> tiles, int numTilesX) :
		tiles_(tiles),
		numTilesX_(numTilesX) {};
	const std::vector<Tile>& getTiles() const;
	int getNumTilesX();
	int getNumTilesY();
	void setTiles(std::vector<Tile>&);
	void layoutTiles(int);
	void setNumTilesX(int);
	void draw(sf::RenderWindow&);
private:
	std::vector<Tile> tiles_;
	int numTilesX_;
};

#endif
