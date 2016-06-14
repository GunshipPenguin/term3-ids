#include "Drawable.h"

void Drawable::setPosition(sf::Vector2f position) {
	position_ = position;
	return;
}

sf::Vector2f Drawable::getPosition() {
	return position_;
}
