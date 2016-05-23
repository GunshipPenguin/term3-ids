#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "Tile.h"
#include "Creep.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class GameScreen: public Screen {
public:
	virtual int run(sf::RenderWindow&);
	void setMapPath(std::string);
	std::vector<Tile> getTileMap();
	int getNumTilesX();
	int getNumTilesY();
	int getTileSize();
	static const int TILEMAP_LOAD_ERROR = 1;
	static const int CREEP_LOAD_ERROR = 2;

private:
	void loadTileMap();
	void drawTiles(sf::RenderWindow&);
	void drawCreeps(sf::RenderWindow&, sf::Texture&);
	void updateCreeps();
	bool loadTiles(std::string);
	void setTilePositions(sf::RenderWindow&);
	void layoutTiles(sf::RenderWindow&);
	std::vector<int> tokenizeIntString(std::string, std::string);

	int numTilesX_;
	int numTilesY_;
	int tileSize_;
	std::string mapPath_;
	std::vector<Tile> tiles_;
	sf::Texture tilesTexture_;
	std::vector<Creep> creeps_;
};

#endif
