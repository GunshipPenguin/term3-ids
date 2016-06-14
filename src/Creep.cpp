#include "Updateable.h"
#include "Tile.h"
#include "Creep.h"
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "CreepPathfinder.h"
#include "TileDrawable.h"

CreepPathfinder Creep::paths_;

Creep::Creep() {}

Creep::Creep(int spawn, int hp, double speed, std::string id) {//tilesize ->drawnTileSize
	int xPos = (spawn%paths_.getNumTilesX())*TileSet::getDrawnSize();
	int yPos = (spawn/paths_.getNumTilesX())*TileSet::getDrawnSize();
	setPosition(sf::Vector2f(xPos, yPos));
	speed_ = speed;
	hp_ = hp;
	id_ = id;
	comingFrom_ = spawn;
	leaked_ = false;
}

std::string Creep::getId() {
	return id_;
}

bool Creep::isLeaked() {
	return leaked_;
}

sf::Vector2f Creep::getFuturePosition(double timeDelta) {
	int drawnSize = TileSet::getDrawnSize();
	sf::Vector2f pos = getPosition();
	float distanceDelta(timeDelta*speed_*drawnSize);

	while (distanceDelta > 0) {
		int goingTo = paths_.getNextByID(comingFrom_);
		if (comingFrom_ == goingTo-1) { //coming from left of goingTo
			float distanceIntoTile = pos.x - (comingFrom_%paths_.getNumTilesX())*drawnSize;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize-distanceIntoTile);
				pos.x = (goingTo%paths_.getNumTilesX())*drawnSize;
				comingFrom_ = goingTo;
			}else {
				pos.x += distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo+1) { //coming from right of goingTo
			float distanceIntoTile = (comingFrom_%paths_.getNumTilesX())*drawnSize - pos.x;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize - distanceIntoTile);
				pos.x = (goingTo%paths_.getNumTilesX())*drawnSize;
				comingFrom_ = goingTo;
			}else {
				pos.x -= distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo-paths_.getNumTilesX()) {//coming from above goingTo
			float distanceIntoTile = pos.y - comingFrom_/paths_.getNumTilesX() * drawnSize;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize - distanceIntoTile);
				pos.y = (goingTo/paths_.getNumTilesX()) * drawnSize;
				comingFrom_ = goingTo;
			}else {
				pos.y += distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo+paths_.getNumTilesX()) {//coming from below goingTo
			float distanceIntoTile = comingFrom_/paths_.getNumTilesX() * drawnSize - pos.y;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize - distanceIntoTile);
				pos.y = (goingTo/paths_.getNumTilesX()) * drawnSize;
				comingFrom_ = goingTo;
			}else {
				pos.y -= distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo) {
			distanceDelta = 0;
			leaked_ = true;
		}
	}
	return pos;
}

void Creep::draw(sf::RenderWindow &window) {
	if (tileSet_) {
		sf::Sprite creepSprite = tileSet_->getSpriteById(1);
		creepSprite.setPosition(getPosition());

		window.draw(creepSprite);
	}
	return;
}

void Creep::update() {
	setPosition(getFuturePosition(delta_));
	return;
}

void Creep::setCreepPathfinder(CreepPathfinder& path) {
	paths_ = path;
}
