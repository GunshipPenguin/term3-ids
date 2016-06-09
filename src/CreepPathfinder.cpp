#include <vector>
#include <queue>
#include <iostream>
#include "CreepPathfinder.h"
#include "Tile.h"

void CreepPathfinder::updatePaths() {
	std::queue<int> q;
	int currTile;
	int numTilesX = tiles_->getNumTilesX();
	int numTilesY = tiles_->getNumTilesY();
	std::vector<Tile> tileMap = tiles_->getTiles();
	std::vector<int> positions(numTilesX*numTilesY,-1);
	
	for (size_t i = 0; i < tileMap.size(); ++i) {
		if (tileMap.at(i).isCreepExit()) {
			exitTile_ = i;
		}
	}
	q.push(exitTile_);
	positions[exitTile_] = exitTile_;
	
	while (!q.empty()) {
		currTile = q.front();
		q.pop();
		if (!tileMap.at(currTile).isBuilt() and tileMap.at(currTile).isCreepWalkable()) {
			
			if (getYById(currTile,numTilesX) != 0 and positions.at(currTile-numTilesX) == -1) {
				q.push(currTile-numTilesX);
				positions[currTile-numTilesX] = currTile;
			}
			if (getXById(currTile,numTilesX)!= 0 and positions.at(currTile-1) == -1) {
				q.push(currTile-1);
				positions[currTile-1] = currTile;
			}
			if (getYById(currTile,numTilesX) < (numTilesY-1) and positions.at(currTile+numTilesX) == -1) {
				q.push(currTile + numTilesX);
				positions[currTile+numTilesX] = currTile;
			}
			if (getXById(currTile,numTilesX) != (numTilesX-1) and positions.at(currTile+1) == -1) {
				q.push(currTile + 1);
				positions[currTile+1] = currTile;
			}
		}
	}
	directedPathGraph_ = positions;
	
}

void CreepPathfinder::setTileMap(const TileMap* tileMap) {
	tiles_ = tileMap;
}

int CreepPathfinder::getNumTilesX() {
	return (*tiles_).getNumTilesX();
}

int CreepPathfinder::getNextByID(int ID) {
	return directedPathGraph_.at(ID);
}

int CreepPathfinder::getXById(int Id, int numTilesX) {
	return Id%numTilesX;
}

int CreepPathfinder::getYById(int Id, int numTilesX) {
	return Id/numTilesX;
}
