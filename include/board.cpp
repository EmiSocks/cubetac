#include "SFML/Graphics.hpp"
#include "grid.cpp"
using namespace sf;

class Board : public Drawable {
private:
	Grid grids[4];
	
public:
	Board() {
		for (int i=0; i<4; i++) grids[i].setPosition(Vector2f(50 + i*185, 150));
	}
	
	virtual void draw(RenderTarget& target, RenderStates states) const {
		// Simply draws the four grids
		for (int i=0; i<4; i++) grids[i].draw(target, states);
	}

};
