#include <SFML/Graphics.hpp>

class Tile {
public:
	Tile(sf::Texture texture, bool buildable, bool creepWalkable)
		: texture_(texture), buildable_(buildable), creepWalkable_(creepWalkable) {}

	void setCreepExit(bool);
	void setCreepSpawn(bool);
	void setCreepWalkable(bool);
	void setBuilt(bool);
	void setBuildable(bool);
	void setTexture(sf::Texture);
	bool isCreepExit();
	bool isCreepSpawn();
	bool isCreepWalkable();
	bool isBuildable();
	bool isBuilt();
	sf::Texture getTexture();

private:
	sf::Texture texture_;
	bool creepSpawn_;
	bool creepExit_;
	bool buildable_;
	bool creepWalkable_;
	bool built_;
};
