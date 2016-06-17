#include "GameScreen.h"
#include "Logger.h"
#include "Tile.h"
#include "TileMap.h"
#include "TileSet.h"
#include "TileDrawable.h"
#include "Wave.h"
#include "Creep.h"
#include "CreepPathfinder.h"

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include <tinyxml2.h>
#include <SFML/Graphics.hpp>

int GameScreen::run(sf::RenderWindow &window) {
	if (! loadTileMap()) {
		Logger::log("GameScreen could not load tiles");
		return TILEMAP_LOAD_ERROR;
	}

	// Set up CreepPathfinder object
	CreepPathfinder creepPathfinder;
	creepPathfinder.setTileMap(&tileMap_);
	creepPathfinder.updatePaths();
	Creep::setCreepPathfinder(creepPathfinder);

	// Load Creeps
	if (! loadCreeps()) {
		Logger::log("GameScreen could not load creeps");
		return CREEP_LOAD_ERROR;
	}

	// Load Towers
	if (! loadTowers()) {
		Logger::log("GameScreen could not load towers");
		return TOWER_LOAD_ERROR;
	}

	// Load Waves
	if (! loadWaves()) {
		Logger::log("Waves could not be loaded");
		return WAVE_LOAD_ERROR;
	}

	// Set up map and window views
	sf::View mapView = getMapView(window.getSize().x, window.getSize().y);
	sf::View menuView = getMenuView(window.getSize().x, window.getSize().y);

	// Event object to poll for
	sf::Event event;

	// Menu shape to fill menuView
	sf::RectangleShape menuShape(menuView.getSize());
	menuShape.setFillColor(sf::Color::Blue);

	// Main loop
	while (true) {
		// Update time delta and wave
		Updateable::updateDelta();

		if (waveOngoing_)
			waves_.front().update();
			lives_ -= waves_.front().getCreepsLeakedSinceLastUpdate();

		// Check to see if the current wave is defeated
		if (waveOngoing_ && waves_.front().isDefeated()) {
			waveOngoing_ = false;
			waves_.pop();
			if (waves_.empty()) {
				Logger::log("All waves defeated");
				return 0;
			}
		}

		// Handle events
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return 0;
			case sf::Event::Resized:
				mapView = getMapView(window.getSize().x, window.getSize().y);
				menuView = getMenuView(window.getSize().x, window.getSize().y);
				menuShape.setSize(menuView.getSize());
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
					waveOngoing_ = true;
				break;
			default:
				break;
			}
		}

		// Clear screen before drawing anything
		window.clear(sf::Color::Black);

		// Draw map
		window.setView(mapView);
		tileMap_.draw(window);

		if (waveOngoing_)
			waves_.front().draw(window);

		// Draw menu
		window.setView(menuView);
		menuShape.setPosition(0, 0);
		window.draw(menuShape);



		window.display();
	}

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
				tileMap_.getNumTilesX()*TileSet::getDrawnSize(),
				tileMap_.getNumTilesY()*TileSet::getDrawnSize()));

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

bool GameScreen::loadWaves() {
	// Load XML document
	tinyxml2::XMLDocument doc;
	std::string creepsFilePath = mapPath_ + "/waves.xml";
	if(doc.LoadFile(creepsFilePath.c_str()) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load waves.xml");
		return false;
	}

	// Get waves element
	tinyxml2::XMLElement* wavesElement = doc.FirstChildElement("waves");
	tinyxml2::XMLElement* currWaveElement = wavesElement->FirstChildElement();

	// Loop through and load all waves
	while(true) {
		if (currWaveElement == 0) {
			break;
		}

		// Get wave entry speed
		int entrySpeed;
		if(currWaveElement->QueryIntAttribute("entrySpeed", &entrySpeed) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not find entry speed of wave in waves.xml");
			return false;
		}

		// Build vector of wave creeps
		std::string creepIdString = currWaveElement->GetText();
		creepIdString.erase(std::remove(creepIdString.begin(),
				creepIdString.end(), '\n'), creepIdString.end());
		creepIdString.erase(std::remove(creepIdString.begin(),
				creepIdString.end(), '\t'), creepIdString.end());
		std::istringstream ss(creepIdString);
		std::string creepId;
		std::vector<Creep> creepVector;

		while(std::getline(ss, creepId, ',')) {
			if (loadedCreeps_.find(creepId) == loadedCreeps_.end()) {
				Logger::log("Creep with id of " + creepId + " does not exist");
				return false;
			}
			// TODO build up creepVector once Devin fixes up Creeps
			Creep currCreep = loadedCreeps_[creepId];
			creepVector.push_back(currCreep);
		}

		waves_.push(Wave(creepVector, entrySpeed));
		currWaveElement = currWaveElement->NextSiblingElement();
	}
	return true;
}

bool GameScreen::loadCreeps() {
	// Load XML document
	tinyxml2::XMLDocument doc;
	std::string creepsFilePath = mapPath_ + "/creeps.xml";
	if(doc.LoadFile(creepsFilePath.c_str()) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load creeps.xml");
		return false;
	}

	// Get creeps element
	tinyxml2::XMLElement* creepsElement = doc.FirstChildElement("creeps");
	tinyxml2::XMLElement* currCreepElement = creepsElement->FirstChildElement();

	// Find creepSpawn
	size_t i;
	int creepSpawn;
	for(i=0;i<tileMap_.getTiles().size();i++) {
		if(tileMap_.getTiles().at(i).isCreepSpawn()) {
			creepSpawn = static_cast<int>(i);
			break;
		}
	}

	// Loop through and load all creeps
	while(true) {
		if (currCreepElement == 0) {
			break;
		}

		// Get creep id
		std::string creepId;
		creepId = currCreepElement->Attribute("id");
		if(creepId.empty()) {
			Logger::log("Invalid or missing id of creep in creeps.xml");
		}

		// Get creep speed
		int creepSpeed;
		if(currCreepElement->QueryIntAttribute("speed", &creepSpeed) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not find speed of creep in creeps.xml");
			return false;
		}
		
		int creepHp;
		if(currCreepElement->QueryIntAttribute("hp", &creepHp) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not find hp of creep in creeps.xml");
			return false;
		}

		// Get creep tileSize
		int creepTileSize;
		if(currCreepElement->QueryIntAttribute("tileSize", &creepTileSize) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not find tileSize of creep in creeps.xml");
			return false;
		}

		// Load creep texture
		sf::Texture creepTexture;
		std::string textureDir = mapPath_ + "/res/" + currCreepElement->Attribute("texture");
		if (!creepTexture.loadFromFile(textureDir)) {
			Logger::log("Could not load creep texture in creeps.xml");
			return false;
		}

		TileSet creepTileSet = TileSet(creepTexture, creepTileSize);
		creepTileSets_[creepId] = creepTileSet;

		Creep creep = Creep(creepSpawn, creepHp, creepSpeed, creepId);
		creep.setTileSet(&creepTileSets_[creepId]);
		loadedCreeps_.insert(std::pair<std::string, Creep> (creepId, creep));

		currCreepElement = currCreepElement->NextSiblingElement();
	}
	return true;
}

bool GameScreen::loadTowers() {
	// Load XML document
	tinyxml2::XMLDocument doc;
	std::string towersFilePath = mapPath_ + "/towers.xml";
	if(doc.LoadFile(towersFilePath.c_str()) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load towers.xml");
		return false;
	}

	// Get towers element
	tinyxml2::XMLElement* towersElement = doc.FirstChildElement("towers");
	tinyxml2::XMLElement* currTowerElement = towersElement->FirstChildElement();

	// Loop through and load all creeps
	while(true) {
		if (currTowerElement == 0) {
			break;
		}

		// Get tower id
		const char* towerIdCharArray;
		towerIdCharArray = currTowerElement->Attribute("id");
		if (! towerIdCharArray) {
			Logger::log("Tower id does not exist in towers.xml");
			return false;
		}
		std::string towerId(towerIdCharArray);
		if(towerId.empty()) {
			Logger::log("Empty tower id in towers.xml");
			return false;
		}

		// Load tower name
		const char* towerNameCharArray;
		towerNameCharArray = currTowerElement->Attribute("name");
		if (! towerNameCharArray) {
			Logger::log("Tower name does not exist in towers.xml");
			return false;
		}
		std::string towerName(towerNameCharArray);
		if(towerName.empty()) {
			Logger::log("Empty tower name in towers.xml");
			return false;
		}


		// Load tower damage
		double towerDamage;
		if (currTowerElement->QueryDoubleAttribute("damage", &towerDamage) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not load tower damage in towers.xml");
			return false;
		}

		// Load tower range
		int towerRange;
		if (currTowerElement->QueryIntAttribute("range", &towerRange) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not load tower range in towers.xml");
			return false;
		}

		// Load tower fire rate
		double towerFireRate;
		if (currTowerElement->QueryDoubleAttribute("fireRate", &towerFireRate) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not load tower texture in towers.xml");
			return false;
		}

		// Load tower projectile speed
		double towerProjectileSpeed;
		if (currTowerElement->QueryDoubleAttribute("projectileSpeed", &towerProjectileSpeed) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not load tower projectile speed in towers.xml");
			return false;
		}

		// Load tower cost
		int towerCost;
		if (currTowerElement->QueryIntAttribute("cost", &towerCost) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not load tower cost in towers.xml");
			return false;
		}

		// Get tower tileSize
		int towerTileSize;
		if(currTowerElement->QueryIntAttribute("tileSize", &towerTileSize) != tinyxml2::XML_NO_ERROR) {
			Logger::log("Could not find tileSize of tower in towers.xml");
			return false;
		}

		// Load tower texture filename
		const char* towerTextureFileNameCharArray;
		towerTextureFileNameCharArray = currTowerElement->Attribute("texture");
		if (! towerTextureFileNameCharArray) {
			Logger::log("Tower texture does not exist in towers.xml");
			return false;
		}
		std::string towerTextureFileName(towerTextureFileNameCharArray);

		// Load tower texture
		sf::Texture towerTexture;
		std::string textureDir = mapPath_ + "/res/" + towerTextureFileName;
		if (!towerTexture.loadFromFile(textureDir)) {
			Logger::log("Could not load tower texture in towers.xml");
			return false;
		}

		TileSet towerTileSet = TileSet(towerTexture, towerTileSize);
		towerTileSets_[towerId] = towerTileSet;

		Tower tower = Tower(towerId, towerName, towerCost, towerDamage,
				towerFireRate, towerProjectileSpeed, &tileMap_);
		tower.setTileSet(&towerTileSets_[towerId]);
		loadedTowers_.insert(std::pair<std::string, Tower> (towerId, tower));

		currTowerElement = currTowerElement->NextSiblingElement();
	}
	return true;
}

bool GameScreen::loadTileMap() {
	// Load XML document
	tinyxml2::XMLDocument doc;
	std::string tileMapPath = mapPath_ + "/tilemap.xml";
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
	int numTilesX = width;
	int numTilesY = height;

	// Load the size of the tileset to be used as the drawn size for all tiles
	int tileSize;
	tinyxml2::XMLElement* tileSetElement = tileMapElement->FirstChildElement(
			"tile_set");
	if(tileSetElement->QueryIntAttribute("size", &tileSize) != tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not find size element of tile_set element");
		return false;
	}
	TileSet::setDrawnSize(tileSize);
	tileSet_.setTileSize(tileSize);

	// Load TileSet texture
	const char* tileSetTexture = tileSetElement->Attribute("src");
	if (tileSetTexture == NULL) {
		Logger::log("No path to texture specified by src attribute of tile_set element");
		return false;
	}
	std::string textureDir = mapPath_ + "/res/" + tileSetElement->Attribute("src");
	if (tilesTexture_.loadFromFile(textureDir) == false) {
		Logger::log("Could not load tile_set texture specified in src attribute");
		return false;
	}
	tilesTexture_.setSmooth(false);
	tileSet_.setTexture(tilesTexture_);

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
	creepSpawnTile --;

	// Load creep exit tile
	int creepExitTile;
	if (tileMapElement->FirstChildElement("creep_exit")->QueryIntAttribute("tile", &creepExitTile)
			!= tinyxml2::XML_NO_ERROR) {
		Logger::log("Could not load info from creep_exit attribute in tilemap.xml");
		return false;
	}
	creepExitTile --;

	// Load tile id data
	tinyxml2::XMLElement* tileDataElement = tileMapElement->FirstChildElement(
			"tile_data");
	std::string tileDataString(tileDataElement->GetText());

	// Fill up the tiles vector
	std::vector<int> idVector = tokenizeIntString(tileDataString, "\n,");
	std::vector<Tile> tiles;
	Tile currTile;

	for(size_t i=0;i<idVector.size();i++) {
		currTile = Tile();

		currTile.setId(idVector.at(i));
		currTile.setTileSet(&tileSet_);

		if (std::find(creepWalkableTiles.begin(),
				creepWalkableTiles.end(), idVector.at(i)) != creepWalkableTiles.end()) {
			currTile.setCreepWalkable(true);
		}
		if (std::find(buildableTiles.begin(),
				buildableTiles.end(), idVector.at(i)) != buildableTiles.end()) {
			currTile.setBuildable(true);
		}

		tiles.push_back(currTile);
	}

	// Ensure that the number of tiles specified is equal to numTilesX_ * numTilesY_
	if (tiles.size() != (size_t) numTilesX * numTilesY) {
		Logger::log("Number of tiles in tilemap.xml differs "
				"from the amount specified in width and height attribute of tile_map");
		return false;
	}

	// Mark creep spawn
	tiles.at(creepSpawnTile).setCreepSpawn(true);

	// Mark creep exit
	tiles.at(creepExitTile).setCreepExit(true);

	// Create TileMap object
	tileMap_.setTiles(tiles);
	tileMap_.setNumTilesX(numTilesX);
	tileMap_.layoutTiles(TileSet::getDrawnSize());

	return true;
}

std::vector<int> GameScreen::tokenizeIntString(std::string str, std::string delimeters) {
	std::string currToken;
	int intToken;

	std::string::size_type lastPos = str.find_first_not_of(delimeters, 0);
	std::string::size_type pos = str.find_first_of(delimeters, lastPos);

	std::vector<int> tokenVector;

	while (std::string::npos != pos || std::string::npos != lastPos) {
		currToken = str.substr(lastPos, pos - lastPos);
		intToken = atoi(currToken.c_str());

		// Skip delimiters
		lastPos = str.find_first_not_of(delimeters, pos);
		pos = str.find_first_of(delimeters, lastPos);

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
