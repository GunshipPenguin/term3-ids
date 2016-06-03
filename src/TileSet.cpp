#include "TileSet.h"

int TileSet::drawnSize_;

sf::Sprite TileSet::getSpriteById(int id) {
	sf::IntRect subRect;
	subRect.left = ((id-1)%(texture_.getSize().x / tileSize_))*tileSize_;
	subRect.top = ((id-1)/(texture_.getSize().x / tileSize_))*tileSize_;
	subRect.width = tileSize_;
	subRect.height = tileSize_;

	sf::Sprite tileSprite(texture_, subRect);

	float scale = drawnSize_ / tileSprite.getLocalBounds().width;
	tileSprite.setScale(scale, scale);

	return tileSprite;
}

void TileSet::setTexture(sf::Texture& texture) {
	texture_ = texture;
	return;
}

void TileSet::setTileSize(int tileSize) {
	tileSize_ = tileSize;
	return;
}

void TileSet::setDrawnSize(int drawnSize) {
	drawnSize_ = drawnSize;
	return;
}

int TileSet::getDrawnSize() {
	return drawnSize_;
}
