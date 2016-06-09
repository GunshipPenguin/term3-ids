#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include "Tile.h"
#include "TileMap.h"

class CreepPathfinder {
public:
	void updatePaths();
	int getNextByID(int);
	void setTileMap(const TileMap* tileMap);
	int getNumTilesX();
private:
	int getYById(int,int);
	int getXById(int,int);
	int exitTile_;
	const TileMap* tiles_;
	std::vector<int> directedPathGraph_;
};	

#endif
