#ifndef TOWER_H
#define TOWER_H

class Tower : public TileDrawable, public Updateable {
public:
	Tower();
	void update();
};

#endif
