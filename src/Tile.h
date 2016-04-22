#include <SFML/Graphics.hpp>

class Tile {
public:
	void setId(int);
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
	int id_;
	sf::Texture texture_;
	bool creepSpawn_;
	bool creepExit_;
	bool buildable_;
	bool creepWalkable_;
	bool built_;
};
