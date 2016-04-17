#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MenuScreen.h"
#include "GameScreen.h"
#include <iostream>

int main()
{
	int width = 300;
	int height = 300;
    sf::RenderWindow window(sf::VideoMode(width, height), "term3-ids");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    GameScreen gameScreen;
    gameScreen.run(window);

    return 0;
}
