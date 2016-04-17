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
	void setTexture(sf::Texture);
	void setXDimen(int);
	void setYDimen(int);
	int getXDimen();
	int getYDimen();
	bool loadFromFile(std::string);


private:
	void parseTileData(const char*);

	std::vector<Tile> tiles_;
	TileSet tileSet_;
	int xDimen_;
	int yDimen_;
	sf::Texture texture_;
	const char* mapFileName_;
};
