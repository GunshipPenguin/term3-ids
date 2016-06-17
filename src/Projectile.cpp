#include "Projectile.h"

void Projectile::update() {
	// TODO Implement the trig. necessary for this
}

void Projectile::draw(sf::RenderWindow& window) {
	sf::Sprite sprite = tileSet_->getSpriteById(1);
	sprite.setPosition(getPosition());

	setCollisionRect(sprite.getLocalBounds());

	window.draw(sprite);
	return;
}
