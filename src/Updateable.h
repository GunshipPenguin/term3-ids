#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include <SFML/Graphics.hpp>

class Updateable {
public:
	static void updateDelta();
	static double getDelta();
	virtual void update() = 0;
private:
	static sf::Clock clock_;
	static double delta_;
	static double totalTime_;
};

#endif
