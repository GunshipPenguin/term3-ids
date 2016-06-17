#ifndef TOWER_H
#define TOWER_H

#include "TileDrawable.h"
#include "Updateable.h"
#include "Projectile.h"
#include "TileMap.h"

class Tower : public TileDrawable, public Updateable {
public:
	Tower(std::string id, std::string name, int cost, double damage,
			double fireRate, double projectileSpeed, const TileMap* tileMap) :
		id_(id),
		name_(name),
		damage_(damage),
		fireRate_(fireRate),
		tileMap_(tileMap) {};
	void draw(sf::RenderWindow&);
	void update();
	const TileMap*& getTileMap() const;
	void setTileMap(const TileMap*& tileMap);

private:
	std::string id_;
	std::string name_;

	double damage_;
	double fireRate_;
	double projectileSpeed;
	double range_;
	int cost_;
	const TileMap* tileMap_;

	float currRotation_;
};

#endif
