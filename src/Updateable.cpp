#include "Updateable.h"
#include <SFML/Graphics.hpp>

sf::Clock Updateable::clock_;
double Updateable::delta_;
double Updateable::totalTime_;

void Updateable::updateDelta() {
	delta_ = 0.1;
	/*
	double tempTime(clock_.getElapsedTime().asSeconds());
	delta_ = tempTime-totalTime_;
	totalTime_=tempTime;
	*/
}
