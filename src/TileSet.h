#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>
#include <string>

class TileSet {
public:
	void setTileSize(int);
	int getTileSize();
	void loadTextureFromFile(std::string);
	sf::Texture getTileTexture(int);

private:
	int tileSize_;
	sf::Texture texture_;
};

#endif
