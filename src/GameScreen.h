#include "Screen.h"
#include "TileMap.h"
#include <string>

class GameScreen : public Screen {
	public:
		virtual int run(sf::RenderWindow&);
        void setMapPath(const char*);
    private:
        void loadTileMap();

        const char* mapPath_;
        TileMap tileMap_;
};
