#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include "Tile.h"

class CreepPathfinder {
public:
	void updatePaths(std::vector<Tile>&,int,int);
	std::vector<int> getPathToEndFromID(int);
	int getNextByID(int,int);
private:
	int getYById(int,int);
	int getXById(int,int);
	int exitTile_;
	std::vector<int> directedPathGraph_;
};	

#endif
