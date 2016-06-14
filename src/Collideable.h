#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H

#include <SFML/Graphics.hpp>

class Collideable {
public:
	sf::FloatRect getCollisionRect();
	void setCollisionRect(sf::FloatRect);
private:
	sf::FloatRect collisionRect_;
};

#endif
