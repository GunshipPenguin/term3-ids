#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MenuScreen.h"
#include "GameScreen.h"
#include "ResourceManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
	int width = 300;
	int height = 300;

	ResourceManager::setBinPath(std::string(argv[0]));

	sf::RenderWindow window(sf::VideoMode(width, height), "term3-ids");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	GameScreen gameScreen;
	gameScreen.setMapPath("/home/rhys/Desktop/term3-ids/maps/example_map");
	gameScreen.run(window);

	return 0;
}
