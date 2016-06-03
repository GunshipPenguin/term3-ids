#include <vector>
#include <queue>
#include <iostream>

#include "CreepPathfinder.h"
#include "Tile.h"

void CreepPathfinder::updatePaths(std::vector<Tile>& tileMap,int numTilesX, int numTilesY) {
	std::vector<int> positions(numTilesX*numTilesY,-1);
	std::queue<int> q;
	int currTile;
	
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

std::vector<int> CreepPathfinder::getPathToEndFromID(int ID) { 
	std::vector<int> path;
	path.push_back(ID);
	while (ID != exitTile_) {
		ID = directedPathGraph_.at(ID);
		path.push_back(ID);
	}
	return path;
}

int CreepPathfinder::getNextByID(int ID, int increase) {
	for (int i = 0; i < increase; ++i) {
		ID = directedPathGraph_.at(ID);
	}
	return ID;
}

int CreepPathfinder::getXById(int Id, int numTilesX) {
	return Id%numTilesX;
}

int CreepPathfinder::getYById(int Id, int numTilesX) {
	return Id/numTilesX;
}
