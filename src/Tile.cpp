#include "Tile.h"
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Tile::setId(int id) {
	id_ = id;
	return;
}

void Tile::draw(sf::RenderWindow &window, sf::Texture &tiles) {
	sf::Sprite sprite = getSpriteById(id_, tiles, tileSize_);
	sprite.setPosition(x_, y_);

	float scale = Drawable::getDrawnSize() / sprite.getLocalBounds().width;
	sprite.setScale(scale, scale);

	window.draw(sprite);
	return;
}

int Tile::getId() {
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

bool Tile::isCreepExit() {
	return creepExit_;
}

bool Tile::isCreepSpawn() {
	return creepSpawn_;
}

bool Tile::isCreepWalkable() {
	return creepWalkable_;
}

bool Tile::isBuilt() {
	return built_;
}

bool Tile::isBuildable() {
	return buildable_;
}
