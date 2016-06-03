#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "Tile.h"
#include "Creep.h"
#include "TileMap.h"
#include "Wave.h"

#include <map>
#include <vector>
#include <queue>
#include <string>
#include <SFML/Graphics.hpp>

class GameScreen: public Screen {
public:
	GameScreen() :
		waveSeq_(1),
		waveOngoing_(false) {};
	virtual int run(sf::RenderWindow&);
	void setMapPath(std::string);
	std::vector<Tile> getTileMap();
	int getNumTilesX();
	int getNumTilesY();
	int getTileSize();
	static const float MENU_SIZE = 0.2;

	static const int TILEMAP_LOAD_ERROR = 1;
	static const int CREEP_LOAD_ERROR = 2;
	static const int WAVE_LOAD_ERROR = 3;

private:
	bool loadCreeps();
	bool loadTileMap();
	bool loadWaves();
	sf::View getMenuView(int, int);
	sf::View getMapView(int, int);
	std::vector<int> tokenizeIntString(std::string, std::string);

	std::string mapPath_;

	sf::Texture tilesTexture_;

	TileMap tileMap_;
	TileSet tileSet_;

	int waveSeq_;
	bool waveOngoing_;
	std::queue<Wave> waves_;

	std::map<std::string, Creep> loadedCreeps_;
	std::map<std::string, TileSet> creepTileSets_;
};

#endif
