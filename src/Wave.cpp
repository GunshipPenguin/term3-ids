#include "Wave.h"

const std::vector<Creep>& Wave::getActiveCreeps() {
	return activeCreeps_;
}

int Wave::getCreepsLeakedSinceLastUpdate() {
	return creepsLeakedSinceLastUpdate_;
	creepsLeakedSinceLastUpdate_ = 0;
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
	// Call update on all creeps, remove leaked creeps
	size_t i;
	for(i=0;i<activeCreeps_.size();i++) {
		activeCreeps_.at(i).update();
	}

	std::vector<Creep>::iterator it = activeCreeps_.begin();
	while(it != activeCreeps_.end()) {
	    if( it->isLeaked() ) {
	        it = activeCreeps_.erase(it);
	    	creepsLeakedSinceLastUpdate_ ++;
	    } else
	    	++it;
	}

	// Send new creeps
	timeSinceLastCreep_ += getDelta();
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
