#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include "Updateable.h"
#include "Drawable.h"
#include "Creep.h"

class Wave: public Updateable, public Drawable {
public:
	Wave() :
		waitingCreeps_(std::vector<Creep>()),
		entrySpeed_(1),
		timeSinceLastCreep_(1) {};
	Wave(std::vector<Creep> creeps, double entrySpeed) :
		waitingCreeps_(creeps),
		entrySpeed_(entrySpeed),
		timeSinceLastCreep_(0) {};
	const std::vector<Creep>& getActiveCreeps();
	void update();
	void draw(sf::RenderWindow&);
	bool isDefeated();

private:
	void sendCreep();
	std::vector<Creep> waitingCreeps_;
	std::vector<Creep> activeCreeps_;
	double entrySpeed_;
	double timeSinceLastCreep_;
};

#endif
