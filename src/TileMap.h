#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include "Tile.h"
#include "TileSet.h"

class TileMap {
public:
	void setTileSize(int);
	int getTileSize();
	void setTile(int, int, Tile);
	Tile getTile(int, int);
	void setXDimen(int);
	void setYDimen(int);
	int getXDimen();
	int getYDimen();
	bool loadFromFile(std::string);

private:
	void parseTileData(std::string);

	std::vector<Tile> tiles_;
	TileSet tileSet_;
	int xDimen_;
	int yDimen_;
	const char* mapFileName_;
};

#endif
