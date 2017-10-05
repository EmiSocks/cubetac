#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
using namespace sf;

class Grid : public Drawable, public Transformable {
private:
	int cells[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	float cellWidth = 35;
	float cellHeight = 35;
	float lineThickness = 2;
	Color lineColor = Color::Black;
	
	int getCell(int i, int j) const { return cells[i][j]; }
	void setCell(int i, int j, int val) { cells[i][j] = val; }
	
public:	
	virtual void draw(RenderTarget& target, RenderStates states) const {
		float width = 4*cellWidth + 5*lineThickness;
		float height = 4*cellHeight + 5*lineThickness;
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
		// Draw each cell content
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				Vector2f targetPosition = Vector2f(position.x + (i*cellWidth) + ((i+1)*lineThickness), position.y + (j*cellHeight) + ((j+1)*lineThickness));
				if (this->getCell(i,j) == 1) {
					CircleShape circle(cellWidth/2);
					circle.setPosition(targetPosition);
					circle.setOutlineColor(lineColor);
					circle.setOutlineThickness(-lineThickness);
					target.draw(circle, states);
				}
				else if (this->getCell(i,j) == 2) {
					RectangleShape rect1(Vector2f(lineThickness, cellHeight));
					RectangleShape rect2(Vector2f(lineThickness, cellHeight));
					rect1.setPosition(targetPosition.x + cellWidth/2 - lineThickness/2, targetPosition.y + cellHeight / 2);
					rect2.setPosition(targetPosition.x + cellWidth/2 - lineThickness/2, targetPosition.y + cellHeight / 2);
					rect1.setOrigin(lineThickness/2, cellHeight/2);
					rect2.setOrigin(lineThickness/2, cellHeight/2);
					rect1.setRotation(45);
					rect2.setRotation(-45);
					rect1.setFillColor(lineColor);
					rect2.setFillColor(lineColor);
					target.draw(rect1, states);
					target.draw(rect2, states);
				}
			}
		}
	}
	
	void getIndicesByCoord(int& i, int& j, Vector2f coord) {
		// This is a 4 instead of a 5 because the last horizontal and vertical lines are not counted
		float width = 4*cellWidth + 4*lineThickness;
		float height = 4*cellHeight + 4*lineThickness;
		Vector2f relativeCoord = coord - (this->getPosition());
		// If the coordinates are inside the grid
		if (relativeCoord.x > 0 && relativeCoord.x < width && relativeCoord.y > 0 && relativeCoord.y < height) {
			i = floor(relativeCoord.x/cellWidth);
			j = floor(relativeCoord.y/cellHeight);
			// If the coordinates are in the border of the cell, set the values to -1
			if (relativeCoord.x - i*cellWidth <= lineThickness || relativeCoord.y - j*cellHeight <= lineThickness) {
				i = j = -1;
			}
		}
		else {
			i = j = -1;
		}
	}
	
	int getCellByCoord(Vector2f coord) {
		int i, j;
		getIndicesByCoord(i, j, coord);
		if (i != -1 && j != -1) return getCell(i, j);
		else return -1;
	}
	
	void setCellByCoord(Vector2f coord, int val) {
		int i, j;
		getIndicesByCoord(i, j, coord);
		if (i != -1 && j != -1 && (val == 0 || val == 1 || val == 2)) setCell(i, j, val);
	}
	
};