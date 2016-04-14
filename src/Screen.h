#include<SFML/Graphics.hpp>

#ifndef SCREEN_H
#define SCREEN_H

class Screen {
public:
	virtual int run(sf::RenderWindow &window) = 0;
};

#endif
