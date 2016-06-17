#include "Tower.h"

void Tower::draw(sf::RenderWindow &window) {
	sf::Sprite baseSprite = tileSet_->getSpriteById(1);
	sf::Sprite rotationSprite = tileSet_->getSpriteById(2);
	baseSprite.setPosition(getPosition());

	rotationSprite.setRotation(currRotation_);

	window.draw(baseSprite);
	window.draw(rotationSprite);
	return;
}

void Tower::update() {
	// TODO put trig stuff for tower updating here
}
