#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int Drawable::drawnSize_;

sf::Sprite Drawable::getSpriteById(int id, sf::Texture &texture, int tileSize) {
	sf::IntRect subRect;
	subRect.left = ((id-1)%(texture.getSize().x / tileSize))*tileSize;
	subRect.top = ((id-1)/(texture.getSize().x / tileSize))*tileSize;
	subRect.width = tileSize;
	subRect.height = tileSize;

	sf::Sprite tileSprite(texture, subRect);
	return tileSprite;
}

void Drawable::setDrawnSize(int drawnTileSize) {
	drawnSize_ = drawnTileSize;
	return;
}

void Drawable::setPosition(int xPosition, int yPosition) {
	x_ = xPosition;
	y_ = yPosition;
	//position_.x = xPosition;
	//position_.y = yPosition;
	return;
}

void Drawable::setTileSize(int tileSize) {
	tileSize_ = tileSize;
	return;
}
