#include "TileMap.h"
#include "TileSet.h"
#include "Logger.h"
#include <string.h>
#include <tinyxml2.h>
#include <iostream>

Tile TileMap::getTile(int x, int y) {
	return tiles_.at(y * xDimen_ + x);
}

void TileMap::setTile(int x, int y, Tile tile) {
	tiles_.at(y * xDimen_ + x) = tile;
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

bool TileMap::loadFromFile(std::string mapPath) {
	// Load XML document
	std::string tileMapPath = mapPath + "/tilemap.xml";
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(tileMapPath.c_str()) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load tilemap.xml");
		return false;
	}

	// Get tile_map element
	tinyxml2::XMLElement* tileMapElement = doc.FirstChildElement("tile_map");

	// Get width and height from the tile_map element
	int width, height;
	if(tileMapElement->QueryIntAttribute("width", &width) != tinyxml2::XML_NO_ERROR){
		Logger::log("Could not find width attribute of tile_map element");
	}
	if (tileMapElement->QueryIntAttribute("height", &height)) {
		Logger::log("Could not find hight attribute of tile_map element");
	}
	setXDimen(width);
	setYDimen(height);

	// Load TileSet size
	tinyxml2::XMLElement* tileSetElement = tileMapElement->FirstChildElement(
			"tile_set");
	int tileSize;
	if(tileSetElement->QueryIntAttribute("size", &tileSize) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not find size element of tile_set element");
		return false;
	}
	tileSet_.setTileSize(tileSize);

	// Load TileSet texture
	const char* tileSetTexture = tileSetElement->Attribute("src");
	if (tileSetTexture == NULL) {
		Logger::log("Could not find texture specified by src attribute of tile_set element");
		return false;
	}

	sf::Texture texture;
	std::string textureDir = mapPath + "/res/" + tileSetElement->Attribute("src");
	if (texture.loadFromFile(textureDir) == false){
		Logger::log("Could not load tile_set texture specified in src attribute");
		return false;
	}
	tileSet_.setTexture(texture);

	// Load tile id data
	tinyxml2::XMLElement* tileDataElement = tileMapElement->FirstChildElement(
			"tile_data");
	std::string tileDataString(tileDataElement->GetText());
	parseTileData(tileDataString);

	return true;
}

void TileMap::parseTileData(std::string tileDataString) {
	std::string::size_type lastPos = tileDataString.find_first_not_of("\n,", 0);
	std::string::size_type pos = tileDataString.find_first_of("\n,", lastPos);

	std::string currToken;
	Tile currTile;

	while (std::string::npos != pos || std::string::npos != lastPos) {
		currToken = tileDataString.substr(lastPos, pos - lastPos);
		currTile = Tile();
		currTile.setId(atoi(currToken.c_str()));
		tiles_.push_back(currTile);

		//Skip delimiters
		lastPos = tileDataString.find_first_not_of("\n,", pos);
		pos = tileDataString.find_first_of("\n,", lastPos);
	}

	return;
}
