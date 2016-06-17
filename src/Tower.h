#ifndef TOWER_H
#define TOWER_H

#include "TileDrawable.h"
#include "Updateable.h"
#include "Projectile.h"

class Tower : public TileDrawable, public Updateable {
public:
	Tower(double damage, double fireRate, TileMap* tileMap) :
		damage_(damage),
		fireRate_(fireRate)_,
		tileMap_(tileMap) {};
	void draw(sf::RenderWindow&);
	void update();
	const TileMap*& getTileMap() const;
	void setTileMap(const TileMap*& tileMap);

private:
	double damage_;
	double fireRate_;
	TileMap* tileMap_;

	float currRotation_;
};

#endif
