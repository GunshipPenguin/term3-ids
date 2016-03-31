#include "Tile.h"
	
void Tile::setCreepExit(bool creepExit) {
	creepExit_ = creepExit;
}

void Tile::setCreepSpawn(bool spawn) {
	spawn = spawn;
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

void Tile::setTexture(sf::Texture texture) {
	texture_ = texture;
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

sf::Texture Tile::getTexture() {
	return texture_;
}
