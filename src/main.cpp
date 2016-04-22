#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MenuScreen.h"
#include "GameScreen.h"
#include "ResourceManager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	int width = 300;
	int height = 300;

	ResourceManager::setBinPath(std::string(argv[0]));
	ResourceManager res;

	std::cout << std::string(argv[0]) << std::endl;
	std::cout << res.getResourcePath() << std::endl;

    sf::RenderWindow window(sf::VideoMode(width, height), "term3-ids");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    GameScreen gameScreen;
    gameScreen.run(window);

    return 0;
}
