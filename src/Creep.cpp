#include "Drawable.h"
#include "Updateable.h"
#include "Tile.h"
#include "Creep.h"
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "CreepPathfinder.h"

CreepPathfinder Creep::paths_;

Creep::Creep() {}

Creep::Creep(int spawn, int hp, double speed, std::string id) {//tilesize ->drawnTileSize
	x_ = (spawn%paths_.getNumTilesX())*TileSet::getDrawnSize();//tileSize;
	y_ = (spawn/paths_.getNumTilesX())*TileSet::getDrawnSize();//tileSize;
	speed_ = speed;
	hp_ = hp;
	id_ = id;
	comingFrom_ = spawn;
}

std::string Creep::getId() {
	return id_;
}

void Creep::getFuturePosition(double timeDelta, float& x, float& y) {
	int drawnSize = TileSet::getDrawnSize();
	float distanceDelta(timeDelta*speed_*drawnSize);
	while (distanceDelta > 0) {
		int goingTo = paths_.getNextByID(comingFrom_);
		if (comingFrom_ == goingTo-1) { //coming from left of goingTo
			float distanceIntoTile = x - (comingFrom_%paths_.getNumTilesX())*drawnSize;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize-distanceIntoTile);
				x = (goingTo%paths_.getNumTilesX())*drawnSize;
				comingFrom_ = goingTo;
			}else {
				x += distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo+1) { //coming from right of goingTo
			float distanceIntoTile = (comingFrom_%paths_.getNumTilesX())*drawnSize -x;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize - distanceIntoTile);
				x = (goingTo%paths_.getNumTilesX())*drawnSize;
				comingFrom_ = goingTo;
			}else {
				x -= distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo-paths_.getNumTilesX()) {//coming from above goingTo
			float distanceIntoTile = y - comingFrom_/paths_.getNumTilesX() * drawnSize;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize - distanceIntoTile);
				y = (goingTo/paths_.getNumTilesX()) * drawnSize;
				comingFrom_ = goingTo;
			}else {
				y += distanceDelta;
				distanceDelta = 0;
			}
		}else if (comingFrom_ == goingTo+paths_.getNumTilesX()) {//coming from below goingTo
			float distanceIntoTile = comingFrom_/paths_.getNumTilesX() * drawnSize -y;
			if (distanceDelta >= drawnSize - distanceIntoTile) {
				distanceDelta -= (drawnSize - distanceIntoTile);
				y = (goingTo/paths_.getNumTilesX()) * drawnSize;
				comingFrom_ = goingTo;
			}else {
				y -= distanceDelta;
				distanceDelta = 0;
			}
		}
	}
}

void Creep::setFuturePosition(double timeDelta, float& x, float& y) {
	getFuturePosition(timeDelta,x,y);
}

float Creep::getXPosition() {
	return x_;
}

float Creep::getYPosition() {
	return y_;
}

void Creep::draw(sf::RenderWindow &window) {
	if (tileSet_) {
		sf::Sprite creepSprite = tileSet_->getSpriteById(1);
		creepSprite.setPosition(x_,y_);

		window.draw(creepSprite);
	}
	return;
}

void Creep::update() {
	setFuturePosition(delta_,x_,y_);
	return;
}

void Creep::setCreepPathfinder(CreepPathfinder& path) {
	paths_ = path;
}
