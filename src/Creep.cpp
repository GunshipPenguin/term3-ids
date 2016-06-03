#include "Drawable.h"
#include "Updateable.h"
#include "Tile.h"
#include "Creep.h"
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "CreepPathfinder.h"

CreepPathfinder Creep::paths_;

Creep::Creep(int spawn, int numTilesX, int tileSize, double speed, std::string id) {//tilesize ->drawnTileSize
	coordinates_.x = (spawn%numTilesX)*tileSize;
	coordinates_.y = (spawn/numTilesX)*tileSize;
	speed_ = speed;
	id_ = id;
	pathPosition_ = 0;
	tileSize_ = tileSize;
	numTilesX_ = numTilesX;
	x_ = coordinates_.x;
	y_ = coordinates_.y;
	path_ = paths_.getPathToEndFromID(spawn);
}

std::string Creep::getId() {
	return id_;
}

int Creep::getPositionByTile() {
	sf::Vector2f centeredCoordinates(coordinates_);
	centeredCoordinates.x += tileSize_/2;
	centeredCoordinates.y += tileSize_/2;
	return numTilesX_*(centeredCoordinates.y/tileSize_) + centeredCoordinates.x/tileSize_;
}

sf::Vector2f Creep::getPosition(bool centered) {
	if (!centered) return coordinates_;
	sf::Vector2f temp(coordinates_);
	temp.x += tileSize_/2;
	temp.y += tileSize_/2;
	return temp;
}

void Creep::setFuturePosition(double timeDelta, float& x, float& y) {
	float distanceIntoTile(static_cast<int>(floor(x))%tileSize_//is vrong
							+(x-floor(x))
							+static_cast<int>(floor(y))%tileSize_
							+(y-floor(y)));
	float distanceDelta(timeDelta*tileSize_*speed_);
	int tileIncrease(floor(distanceDelta)/tileSize_);
	
	distanceIntoTile += distanceDelta - (tileIncrease * tileSize_);
	
	if (distanceIntoTile > tileSize_) {//might happen if creep was close to end of tile
		tileIncrease += 1;
		distanceIntoTile -= tileSize_;//now it is guaranteed to be accurate: lolNope
	}
	
	
	if (pathPosition_ + tileIncrease < path_.size()) {
		x = (path_[pathPosition_+tileIncrease]%numTilesX_)*tileSize_;
		y = (path_[pathPosition_+tileIncrease]/numTilesX_)*tileSize_;
	} else {
		pathPosition_ = path_.size() - 1;
		//perhaps a boolean return?
		return;
	}
	//coming from above
	if (path_[pathPosition_+tileIncrease] == path_[pathPosition_+tileIncrease+1]-numTilesX_) {
		y += distanceIntoTile;
	}
	//coming from below
	else if (path_[pathPosition_+tileIncrease] == path_[pathPosition_+tileIncrease+1]+numTilesX_) {
		y -= distanceIntoTile; 
	}
	//coming from the left
	else if (path_[pathPosition_+tileIncrease] == path_[pathPosition_+tileIncrease+1]-1) {
		x += distanceIntoTile;
	}
	//coming from the right
	else if (path_[pathPosition_+tileIncrease] == path_[pathPosition_+tileIncrease+1]+1) {
		x -= distanceIntoTile; 
	}
	
	pathPosition_ += tileIncrease;
	
	return;
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
