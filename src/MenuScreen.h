#include "Screen.h"

class MenuScreen : public Screen {
	public:
        static const int LOAD_MAP = 1;
        static const int FONT_LOAD_FAILED = 2;
        static const int LOGIC_ERROR = 3;
		virtual int run(sf::RenderWindow &window);
		const char* getMapPath();
    private:
        const char* mapPath_;
};
