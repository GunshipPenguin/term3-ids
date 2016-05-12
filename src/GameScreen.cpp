#include "GameScreen.h"
#include "Logger.h"
#include "Tile.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <tinyxml2.h>
#include <SFML/Graphics.hpp>

int GameScreen::run(sf::RenderWindow &window) {
	if (! loadTiles(mapPath_)) {
		Logger::log("GameScreen could not load tiles");
		return TILEMAP_LOAD_ERROR;
	}
	layoutTiles(window);

	sf::View mapView = getMapView(window.getSize().x, window.getSize().y);
	sf::View menuView = getMenuView(window.getSize().x, window.getSize().y);

	sf::Event event;

	sf::RectangleShape menuShape(menuView.getSize());
	menuShape.setFillColor(sf::Color::Blue);

	while (true) {
		window.clear(sf::Color::Black);

		// Handle events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::Resized) {
				mapView = getMapView(window.getSize().x, window.getSize().y);
				menuView = getMenuView(window.getSize().x, window.getSize().y);
				menuShape.setSize(menuView.getSize());
			}
		}
		// Draw map
		window.setView(mapView);
		drawTiles(window);

		// Draw menu
		window.setView(menuView);
		menuShape.setPosition(0, 0);
		window.draw(menuShape);


		window.display();
	}

	sf::Time t1 = sf::seconds(500.0f);
	sf::sleep(t1);

	return 0;
}

sf::View GameScreen::getMenuView(int screenWidth, int screenHeight) {
	sf::View menuView(sf::FloatRect(0, 0, screenWidth*MENU_SIZE, screenHeight));
	menuView.setViewport(sf::FloatRect(1-MENU_SIZE, 0, MENU_SIZE, 1));
	return menuView;
}

sf::View GameScreen::getMapView(int screenWidth, int screenHeight) {
	// Fit the mapView around all the tiles
	sf::View mapView(sf::FloatRect(0, 0,
				numTilesX_*Drawable::getDrawnSize(),
				numTilesY_*Drawable::getDrawnSize()));

	int xAvaliable = screenWidth * (1-MENU_SIZE);

	float windowRatio = xAvaliable / (float) screenHeight;
	float viewRatio = mapView.getSize().x / (float) mapView.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	if (horizontalSpacing) {
		posY = 0;
		sizeY = 1;
		sizeX = (sizeY*screenHeight*viewRatio)/screenWidth;
		posX = (1-MENU_SIZE-sizeX)/2;
	} else {
		posX = 0;
		sizeX = (1-MENU_SIZE);
		sizeY = (sizeX*screenWidth*viewRatio)/screenHeight;
		posY= (1-sizeY) / 2;
	}

	mapView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
	return mapView;
}

void GameScreen::drawTiles(sf::RenderWindow &window) {
	size_t i;
	for (i=0;i<tiles_.size();i++) {
		tiles_.at(i).draw(window, tilesTexture_);
	}
	return;
}

void GameScreen::layoutTiles(sf::RenderWindow &window) {
	size_t i;
	sf::Vector2f position;
	int x, y;
	for (i=0;i<tiles_.size();i++) {
		x = (i % numTilesX_) * Drawable::getDrawnSize();
		y = (i / numTilesX_) * Drawable::getDrawnSize();
		tiles_.at(i).setPosition(x, y);
	}
	return;
}

bool GameScreen::loadTiles(std::string mapPath) {
	// Load XML document
	tinyxml2::XMLDocument doc;
	std::string tileMapPath = mapPath + "/tilemap.xml";
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
		Logger::log("Could not find height attribute of tile_map element");
	}
	numTilesX_ = width;
	numTilesY_ = height;

	// Load TileSet size
	tinyxml2::XMLElement* tileSetElement = tileMapElement->FirstChildElement(
			"tile_set");
	if(tileSetElement->QueryIntAttribute("size", &tileSize_) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not find size element of tile_set element");
		return false;
	}
	Drawable::setDrawnSize(tileSize_);

	// Load creep walkable tiles
	std::string creepWalkableTilesString(tileSetElement->Attribute("creep_walkable"));
	std::vector<int> creepWalkableTiles = tokenizeIntString(creepWalkableTilesString, ",");

	// Load buildable tiles
	std::string buildableTilesString(tileSetElement->Attribute("buildable"));
	std::vector<int> buildableTiles = tokenizeIntString(buildableTilesString, ",");

	// Load creep spawn tile
	int creepSpawnTile;
	if (tileMapElement->FirstChildElement("creep_spawn")->QueryIntAttribute("tile", &creepSpawnTile)
			!= tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load info from creep_spawn attribute in tilemap.xml");
		return false;
	}

	// Load creep exit tile
	int creepExitTile;
	if (tileMapElement->FirstChildElement("creep_exit")->QueryIntAttribute("tile", &creepExitTile)
			!= tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load info from creep_exit attribute in tilemap.xml");
		return false;
	}

	// Load TileSet texture
	const char* tileSetTexture = tileSetElement->Attribute("src");
	if (tileSetTexture == NULL) {
		Logger::log("No path to texture specified by src attribute of tile_set element");
		return false;
	}

	std::string textureDir = mapPath + "/res/" + tileSetElement->Attribute("src");
	if (tilesTexture_.loadFromFile(textureDir) == false) {
		Logger::log("Could not load tile_set texture specified in src attribute");
		return false;
	}

	// Load tile id data
	tinyxml2::XMLElement* tileDataElement = tileMapElement->FirstChildElement(
			"tile_data");
	std::string tileDataString(tileDataElement->GetText());

	std::vector<int> idVector = tokenizeIntString(tileDataString, "\n,");
	size_t i;
	Tile currTile;

	for(i=0;i<idVector.size();i++) {
		currTile = Tile();

		currTile.setId(idVector.at(i));
		currTile.setTileSize(tileSize_);


		if (std::find(creepWalkableTiles.begin(),
				creepWalkableTiles.end(), idVector.at(i)) != creepWalkableTiles.end()) {
			currTile.setCreepWalkable(true);
		}
		if (std::find(buildableTiles.begin(),
				buildableTiles.end(), idVector.at(i)) != buildableTiles.end()) {
			currTile.setBuildable(true);
		}

		tiles_.push_back(currTile);
	}

	// Ensure that the number of tiles specified is equal to numTilesX_ * numTilesY_
	if (tiles_.size() != (unsigned int) numTilesX_ * numTilesY_) {
		Logger::log("Number of tiles in tilemap.xml differs "
				"from the amount specified in width and height attribute of tile_map");
		return false;
	}

	// Mark creep spawn
	tiles_.at(creepSpawnTile).setCreepSpawn(true);

	// Mark creep exit
	tiles_.at(creepExitTile).setCreepExit(true);

	return true;
}

std::vector<int> GameScreen::tokenizeIntString(std::string str, std::string delimetirs) {
	std::string currToken;
	int intToken;

	std::string::size_type lastPos = str.find_first_not_of("\n,", 0);
	std::string::size_type pos = str.find_first_of("\n,", lastPos);

	std::vector<int> tokenVector;

	while (std::string::npos != pos || std::string::npos != lastPos) {
		currToken = str.substr(lastPos, pos - lastPos);
		intToken = atoi(currToken.c_str());

		// Skip delimiters
		lastPos = str.find_first_not_of("\n,", pos);
		pos = str.find_first_of("\n,", lastPos);

		// Special case where currToken is the final tab
		if (intToken == 0)
			continue;

		tokenVector.push_back(intToken);
	}
	return tokenVector;
}

void GameScreen::setMapPath(std::string mapPath) {
	mapPath_ = mapPath;
	return;
}
