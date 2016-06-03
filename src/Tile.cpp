#include "Tile.h"
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Tile::setId(int id) {
	id_ = id;
	return;
}

void Tile::draw(sf::RenderWindow &window) {
	if(tileSet_) {
		sf::Sprite sprite = tileSet_->getSpriteById(id_);
		sprite.setPosition(x_, y_);
		window.draw(sprite);
	}
	return;
}

int Tile::getId() const {
	return id_;
}

void Tile::setCreepExit(bool creepExit) {
	creepExit_ = creepExit;
}

void Tile::setCreepSpawn(bool spawn) {
	creepSpawn_ = spawn;
}

void Tile::setCreepWalkable(bool creepWalkable) {
	creepWalkable_ = creepWalkable;
}

void Tile::setBuilt(bool built) {
	built_ = built;
}

void Tile::setBuildable(bool buildable) {
	buildable_ = buildable;
}

bool Tile::isCreepExit() const {
	return creepExit_;
}

bool Tile::isCreepSpawn() const {
	return creepSpawn_;
}

bool Tile::isCreepWalkable() const {
	return creepWalkable_;
}

bool Tile::isBuilt() const {
	return built_;
}

bool Tile::isBuildable() const {
	return buildable_;
}
