#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include "Updateable.h"
#include "Drawable.h"
#include "Creep.h"

class Wave: public Updateable, public Drawable {
public:
	Wave() :
		activeCreeps_(std::vector<Creep>()),
		entrySpeed_(1),
		timeSinceLastCreep_(1) {};
	Wave(std::vector<Creep> creeps, int entrySpeed) :
		activeCreeps_(creeps),
		entrySpeed_(entrySpeed),
		timeSinceLastCreep_(0) {};
	const std::vector<Creep>& getActiveCreeps();
	void update();
	void draw(sf::RenderWindow&);
	bool isDefeated();

private:
	void sendCreep();
	std::vector<Creep> activeCreeps_;
	int entrySpeed_;
	int timeSinceLastCreep_;
	std::vector<Creep> waitingCreeps_;
};

#endif
