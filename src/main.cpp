#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MenuScreen.h"

int main()
{
	int width = 300;
	int height = 300;
    sf::RenderWindow window(sf::VideoMode(width, height), "term3-ids");
    
    MenuScreen menuScreen = MenuScreen();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
