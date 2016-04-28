#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable {
public:
	virtual void draw(sf::RenderWindow &window, sf::Texture &tiles) = 0;
	void setTileSize(int tileSize);
	void setPosition(int, int);
	static void setDrawnSize(int);

protected:
	sf::Sprite getSpriteById(int id, sf::Texture&, int tileSize);
	int tileSize_;
	int x_;
	int y_;
	static int drawnSize_;

};

#endif
