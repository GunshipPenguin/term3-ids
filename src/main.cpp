#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MenuScreen.h"
#include "GameScreen.h"
#include "Logger.h"
#include "ResourceManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
	int width = 300;
	int height = 300;

	ResourceManager::setBinPath(std::string(argv[0]));

	sf::RenderWindow window(sf::VideoMode(width, height), "term3-ids");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	if (argc != 2) {
		Logger::log("Map path not specified");
		return 1;
	}

	GameScreen gameScreen;
	std::string mapPath(argv[1]);
	std::cout << mapPath << std::endl;
	gameScreen.setMapPath(mapPath);

	gameScreen.run(window);

	return 0;
}
