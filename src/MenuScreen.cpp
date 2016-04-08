#include "MenuScreen.h"
#include <string>
#include <iostream>
#include <algorithm>

int MenuScreen::run(sf::RenderWindow& window) {
    std::string currMapPath;
    sf::Vector2u windowSize = window.getSize();
    sf::Font font;
    sf::Text text;

    if (!font.loadFromFile("../res/open-sans.semibold.ttf")) {
        return FONT_LOAD_FAILED;
    }

    text.setFont(font);
    text.setCharacterSize(std::max(static_cast<int>(windowSize.x/50.0),10));
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            switch (event.type) {

            case sf::Event::TextEntered:
                // Using only ASCII characters
                if (event.text.unicode < 128) {
                    // Backspace character is 8, removes last character in path if path has characters
                    if (event.text.unicode == 8 and currMapPath.size() > 0) {
                        currMapPath.erase(currMapPath.size()-1);
                    }
                    else if(event.text.unicode != 8) {
                        currMapPath += static_cast<char>(event.text.unicode);
                    }
                }

            case sf::Event::KeyPressed:
                //submits path if enter pressed
                if (event.key.code == sf::Keyboard::Return) {
                        mapPath_ = currMapPath.c_str();
                        return LOAD_MAP;
                }

            default:
                break;
            }

            text.setString(currMapPath);
            text.setPosition(0, windowSize.y/2.0);

            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();
        }
    }
    return LOGIC_ERROR;
}

const char* MenuScreen::getMapPath() {
    return mapPath_;
}
