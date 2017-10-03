#include "SFML/Graphics.hpp"
using namespace sf;

class Grid : public Drawable, public Transformable {
private:
	int cellWidth = 50;
	int cellHeight = 50;
	int lineThickness = 5;
	Color lineColor = Color::Black;
	
	virtual void draw(RenderTarget& target, RenderStates states) const {
		int width = 4*cellWidth + 5*lineThickness;
		int height = 4*cellHeight + 5*lineThickness;
		Vector2f position = this->getPosition();
		// Draw the grid lines
		for (int i=0; i<=4; i++) {
			// Draw the horizontal line
			RectangleShape hLine(Vector2f(width, lineThickness));
			hLine.setPosition(position.x, position.y + i*(cellHeight+lineThickness));
			hLine.setFillColor(lineColor);
			target.draw(hLine, states);
			// Draw the vertical line
			RectangleShape vLine(Vector2f(lineThickness, height));
			vLine.setPosition(position.x + i*(cellWidth+lineThickness), position.y);
			vLine.setFillColor(lineColor);
			target.draw(vLine, states);
		}
	}
	
};