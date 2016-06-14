#include "Collideable.h"

sf::FloatRect Collideable::getCollisionRect() {
	return collisionRect_;
}

void Collideable::setCollisionRect(sf::FloatRect collisionRect) {
	collisionRect_ = collisionRect;
	return;
}
