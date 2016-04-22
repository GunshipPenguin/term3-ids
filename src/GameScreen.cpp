#include "GameScreen.h"
#include <string>
#include <fstream>
#include <iostream>

int GameScreen::run(sf::RenderWindow &window) {
	loadTileMap();
	return 0;
}

void GameScreen::loadTileMap() {
	tileMap_.loadFromFile(mapPath_);
	return;
}

void GameScreen::setMapPath(std::string mapPath) {
	mapPath_ = mapPath;
	return;
}
