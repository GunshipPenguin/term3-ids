#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "TileDrawable.h"
#include "Updateable.h"
#include "Collideable.h"
#include <SFML/Graphics.hpp>

class Projectile : public TileDrawable, public Updateable, public Collideable {
public:
	Projectile(double damage, double speed) :
		damage_(damage),
		speed_(speed) {};
	void draw(sf::RenderWindow&);
	void update();
private:
	double damage_;
	double speed_;
};

#endif
