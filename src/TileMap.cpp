#include "TileMap.h"
#include "TileSet.h"
#include <string.h>
#include <tinyxml2.h>

Tile TileMap::getTile(int x, int y) {
	return tiles_.at(y * xDimen_ + x);
}

void TileMap::setTile(int x, int y, Tile tile) {
	tiles_.at(y * xDimen_ + x) = tile;
	return;
}

void TileMap::setTexture(sf::Texture texture) {
	texture_ = texture;
	return;
}

int TileMap::getXDimen() {
	return xDimen_;
}

void TileMap::setXDimen(int xDimen) {
	xDimen_ = xDimen;
	return;
}

void TileMap::setYDimen(int yDimen) {
	yDimen_ = yDimen;
	return;
}

int TileMap::getYDimen() {
	return yDimen_;
}

bool TileMap::loadFromFile(std::string path) {
	// Load XML document
	tinyxml2::XMLDocument doc;
	doc.LoadFile(path.c_str());

	// Get tile_map element
	tinyxml2::XMLElement* tileMapElement = doc.FirstChildElement("tile_map");

	// Get width and height from the tile_map element
	int width, height;
	tileMapElement->QueryIntAttribute("width", &width);
	tileMapElement->QueryIntAttribute("height", &height);

	// Load TileSet
	tinyxml2::XMLElement* tileSetElement = tileMapElement->FirstChildElement(
			"tile_set");
	int tileSize;
	tileSetElement->QueryIntAttribute("size", &tileSize);
	tileSet_.setTileSize(tileSize);
	tileSet_.loadTextureFromFile(path + tileSetElement->Attribute("src"));

	setXDimen(width);
	setYDimen(height);

	sf::Texture texture;
	texture.loadFromFile(tileSetElement->Attribute("src"));
	setTexture(texture);

	tinyxml2::XMLElement* tileDataElement = tileMapElement->FirstChildElement(
			"tile_data");
	parseTileData(tileDataElement->GetText());

	return true;
}

void TileMap::parseTileData(const char* tileData) {
	char* tileDataCopy = strdup(tileData);
	char* currTileId = strtok(tileDataCopy, ",\n");

	Tile currTile;
	while (currTileId != NULL) {
		currTile = Tile();
		currTile.setId(atoi(currTileId));
		tiles_.push_back(currTile);

		currTileId = strtok(NULL, ",\n");
	}
}
