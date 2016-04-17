#include <SFML/Graphics.hpp>
#include <string>

#ifndef SRC_TILESET_H_
#define SRC_TILESET_H_

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

#endif /* SRC_TILESET_H_ */
