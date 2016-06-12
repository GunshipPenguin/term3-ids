#include "Wave.h"

const std::vector<Creep>& Wave::getActiveCreeps() {
	return activeCreeps_;
}

bool Wave::isDefeated() {
	return activeCreeps_.empty() && waitingCreeps_.empty();
}

void Wave::sendCreep() {
	if (waitingCreeps_.empty()) {
		return;
	}

	Creep creepToSend = waitingCreeps_.back();
	waitingCreeps_.pop_back();
	activeCreeps_.push_back(creepToSend);

	return;
}

void Wave::update() {
	size_t i;
	for(i=0;i<activeCreeps_.size();i++) {
		activeCreeps_.at(i).update();
	}

	timeSinceLastCreep_ += delta_;
	if (timeSinceLastCreep_ >= entrySpeed_ && !waitingCreeps_.empty()) {
		timeSinceLastCreep_ = 0;
		sendCreep();
	}

	return;
}

void Wave::draw(sf::RenderWindow &window) {
	for(size_t i=0;i<activeCreeps_.size();i++) {
		activeCreeps_.at(i).draw(window);
	}
	return;
}
