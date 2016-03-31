#include <vector>
#include <string>
#include "Tile.h"

class TileMap {
public:
	TileMap(int tileSize, int xDimen, int yDimen, const char* mapFileName) 
		: tileSize_(tileSize), xDimen_(xDimen), yDimen_(yDimen), mapFileName_(mapFileName) {}
		
	void setTileSize(int);
	int getTileSize();
	void setTile(int, int, Tile);
	Tile getTile(int, int);
	int getXDimen();
	int getYDimen();
		
private:
	int tileSize_;
	std::vector<std::vector<Tile> > tiles_;
	int xDimen_;
	int yDimen_;
	const char* mapFileName_;
};
