#include "Screen.h"
#include "TileMap.h"
#include <string>

class GameScreen: public Screen {
public:
	virtual int run(sf::RenderWindow&);
	void setMapPath(std::string);
private:
	void loadTileMap();

	std::string mapPath_;
	TileMap tileMap_;
};
