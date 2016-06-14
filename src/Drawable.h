#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable {
public:
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	virtual void draw(sf::RenderWindow&) = 0;
private:
	sf::Vector2f position_;
};

#endif
