#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>

class TileSet {
public:
	TileSet() :
		texture_(sf::Texture()),
		tileSize_(16) {};
	TileSet(sf::Texture texture, int tileSize) :
		texture_(texture),
		tileSize_(tileSize) {};
	sf::Sprite getSpriteById(int);
	void setTileSize(int);
	void setTexture(sf::Texture&);
	static void setDrawnSize(int);
	static int getDrawnSize();
private:
	sf::Texture texture_;
	int tileSize_;
	static int drawnSize_;
};

#endif
