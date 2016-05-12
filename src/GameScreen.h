#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class GameScreen: public Screen {
public:
	virtual int run(sf::RenderWindow&);
	void setMapPath(std::string);
	static const int TILEMAP_LOAD_ERROR = 1;
	static const float MENU_SIZE = 0.2;

private:
	void loadTileMap();
	void drawTiles(sf::RenderWindow&);
	bool loadTiles(std::string);
	void setTilePositions(sf::RenderWindow&);
	void layoutTiles(sf::RenderWindow&);
	sf::View getMenuView(int, int);
	sf::View getMapView(int, int);
	std::vector<int> tokenizeIntString(std::string, std::string);

	int numTilesX_;
	int numTilesY_;
	int tileSize_;
	std::string mapPath_;
	std::vector<Tile> tiles_;
	sf::Texture tilesTexture_;
};

#endif
