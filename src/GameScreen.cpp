#include "GameScreen.h"
#include <string>
#include <fstream>
#include <tinyxml2.h>
#include <iostream>

int GameScreen::run(sf::RenderWindow &window) {
    loadTileMap();
    return 0;
}

void GameScreen::loadTileMap() {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(mapPath_);

    tinyxml2::XMLElement* tileMapElement = doc.FirstChildElement("tile_map");
    tinyxml2::XMLElement* tileSetElement = tileMapElement->FirstChildElement("tile_set");

    int width, height;
    tileMapElement->QueryIntAttribute("width", &width);
    tileMapElement->QueryIntAttribute("height", &height);

    int tileSize;
    tileSetElement->QueryIntAttribute("size", &tileSize);

    TileMap tileMap;

    tileMap.setXDimen(width);
    tileMap.setYDimen(height);
    tileMap.setTileSize(tileSize);

    sf::Texture texture;
    texture.loadFromFile(tileSetElement->Attribute("src"));
    tileMap.setTexture(texture);

    return;
}

void GameScreen::setMapPath(const char* mapPath) {
    mapPath_ = mapPath;
    return;
}
