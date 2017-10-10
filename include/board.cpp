#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "grid.cpp"
// Might have miscounted, check later
#define N_WIN_LINES 76
using namespace sf;
using namespace std;

class Board : public Drawable {
private:
	Grid grids[4];
	
	int x = 50;
	int y = 150;
	
	vector<vector<vector<int>>> winLines;
	
	int isCompleteLine(vector<vector<int>> line) const {
		// Saves the value of the first cell in the line
		int val = getCell(line[0][0], line[0][1], line[0][2]);
		// Checks if the other cells are equal to the first
		if (getCell(line[1][0], line[1][1], line[1][2]) == val &&
			getCell(line[2][0], line[2][1], line[2][2]) == val &&
			getCell(line[3][0], line[3][1], line[3][2]) == val) {
			return val;
		}
		else return 0;
	}
	
public:

	Board() {
		// Initialize the 4 grids
		for (int i=0; i<4; i++) grids[i].setPosition(Vector2f(x + i*185, y));
		// Initialize the winning lines
		int wLines[N_WIN_LINES][4][3] = {
			// Vertical lines
			{ {0,0,0}, {1,0,0}, {2,0,0}, {3,0,0} },
			{ {0,1,0}, {1,1,0}, {2,1,0}, {3,1,0} },
			{ {0,2,0}, {1,2,0}, {2,2,0}, {3,2,0} },
			{ {0,3,0}, {1,3,0}, {2,3,0}, {3,3,0} },
			{ {0,0,1}, {1,0,1}, {2,0,1}, {3,0,1} },
			{ {0,1,1}, {1,1,1}, {2,1,1}, {3,1,1} },
			{ {0,2,1}, {1,2,1}, {2,2,1}, {3,2,1} },
			{ {0,3,1}, {1,3,1}, {2,3,1}, {3,3,1} },
			{ {0,0,2}, {1,0,2}, {2,0,2}, {3,0,2} },
			{ {0,1,2}, {1,1,2}, {2,1,2}, {3,1,2} },
			{ {0,2,2}, {1,2,2}, {2,2,2}, {3,2,2} },
			{ {0,3,2}, {1,3,2}, {2,3,2}, {3,3,2} },
			{ {0,0,3}, {1,0,3}, {2,0,3}, {3,0,3} },
			{ {0,1,3}, {1,1,3}, {2,1,3}, {3,1,3} },
			{ {0,2,3}, {1,2,3}, {2,2,3}, {3,2,3} },
			{ {0,3,3}, {1,3,3}, {2,3,3}, {3,3,3} },
			// Horizontal lines
			{ {0,0,0}, {0,1,0}, {0,2,0}, {0,3,0} },
			{ {0,0,1}, {0,1,1}, {0,2,1}, {0,3,1} },
			{ {0,0,2}, {0,1,2}, {0,2,2}, {0,3,2} },
			{ {0,0,3}, {0,1,3}, {0,2,3}, {0,3,3} },
			{ {1,0,0}, {1,1,0}, {1,2,0}, {1,3,0} },
			{ {1,0,1}, {1,1,1}, {1,2,1}, {1,3,1} },
			{ {1,0,2}, {1,1,2}, {1,2,2}, {1,3,2} },
			{ {1,0,3}, {1,1,3}, {1,2,3}, {1,3,3} },
			{ {2,0,0}, {2,1,0}, {2,2,0}, {2,3,0} },
			{ {2,0,1}, {2,1,1}, {2,2,1}, {2,3,1} },
			{ {2,0,2}, {2,1,2}, {2,2,2}, {2,3,2} },
			{ {2,0,3}, {2,1,3}, {2,2,3}, {2,3,3} },
			{ {3,0,0}, {3,1,0}, {3,2,0}, {3,3,0} },
			{ {3,0,1}, {3,1,1}, {3,2,1}, {3,3,1} },
			{ {3,0,2}, {3,1,2}, {3,2,2}, {3,3,2} },
			{ {3,0,3}, {3,1,3}, {3,2,3}, {3,3,3} },
			// Longitudinal lines
			{ {0,0,0}, {0,0,1}, {0,0,2}, {0,0,3} },
			{ {1,0,0}, {1,0,1}, {1,0,2}, {1,0,3} },
			{ {2,0,0}, {2,0,1}, {2,0,2}, {2,0,3} },
			{ {3,0,0}, {3,0,1}, {3,0,2}, {3,0,3} },
			{ {0,1,0}, {0,1,1}, {0,1,2}, {0,1,3} },
			{ {1,1,0}, {1,1,1}, {1,1,2}, {1,1,3} },
			{ {2,1,0}, {2,1,1}, {2,1,2}, {2,1,3} },
			{ {3,1,0}, {3,1,1}, {3,1,2}, {3,1,3} },
			{ {0,2,0}, {0,2,1}, {0,2,2}, {0,2,3} },
			{ {1,2,0}, {1,2,1}, {1,2,2}, {1,2,3} },
			{ {2,2,0}, {2,2,1}, {2,2,2}, {2,2,3} },
			{ {3,2,0}, {3,2,1}, {3,2,2}, {3,2,3} },
			{ {0,3,0}, {0,3,1}, {0,3,2}, {0,3,3} },
			{ {1,3,0}, {1,3,1}, {1,3,2}, {1,3,3} },
			{ {2,3,0}, {2,3,1}, {2,3,2}, {2,3,3} },
			{ {3,3,0}, {3,3,1}, {3,3,2}, {3,3,3} },
			// Diagonal lines (XY plane)
			{ {0,0,0}, {1,1,0}, {2,2,0}, {3,3,0} },
			{ {0,0,1}, {1,1,1}, {2,2,1}, {3,3,1} },
			{ {0,0,2}, {1,1,2}, {2,2,2}, {3,3,2} },
			{ {0,0,3}, {1,1,3}, {2,2,3}, {3,3,3} },
			{ {0,3,0}, {1,2,0}, {2,1,0}, {3,0,0} },
			{ {0,3,1}, {1,2,1}, {2,1,1}, {3,0,1} },
			{ {0,3,2}, {1,2,2}, {2,1,2}, {3,0,2} },
			{ {0,3,3}, {1,2,3}, {2,1,3}, {3,0,3} },
			// Diagonal lines (YZ plane)
			{ {0,0,0}, {0,1,1}, {0,2,2}, {0,3,3} },
			{ {1,0,0}, {1,1,1}, {1,2,2}, {1,3,3} },
			{ {2,0,0}, {2,1,1}, {2,2,2}, {2,3,3} },
			{ {3,0,0}, {3,1,1}, {3,2,2}, {3,3,3} },
			{ {0,0,3}, {0,1,2}, {0,2,1}, {0,3,0} },
			{ {1,0,3}, {1,1,2}, {1,2,1}, {1,3,0} },
			{ {2,0,3}, {2,1,2}, {2,2,1}, {2,3,0} },
			{ {3,0,3}, {3,1,2}, {3,2,1}, {3,3,0} },
			// Diagonal lines (ZX plane)
			{ {0,0,0}, {1,0,1}, {2,0,2}, {3,0,3} },
			{ {0,1,0}, {1,1,1}, {2,1,2}, {3,1,3} },
			{ {0,2,0}, {1,2,1}, {2,2,2}, {3,2,3} },
			{ {0,3,0}, {1,3,1}, {2,3,2}, {3,3,3} },
			{ {3,0,0}, {2,0,1}, {1,0,2}, {0,0,3} },
			{ {3,1,0}, {2,1,1}, {1,1,2}, {0,1,3} },
			{ {3,2,0}, {2,2,1}, {1,2,2}, {0,2,3} },
			{ {3,3,0}, {2,3,1}, {1,3,2}, {0,3,3} },
			// Diagonal lines (corners)
			{ {0,0,0}, {1,1,1}, {2,2,2}, {3,3,3} },
			{ {0,0,3}, {1,1,2}, {2,2,1}, {3,3,0} },
			{ {0,3,0}, {1,2,1}, {2,1,2}, {3,0,3} },
			{ {0,3,3}, {1,2,2}, {2,1,1}, {3,0,0} }
		};
		
		//winLines (N_WIN_LINES, vector<vector<int>>(4, vector<int>(3)));
		
		for (int n=0; n<N_WIN_LINES; n++) {
			vector<vector<int>> line;
			for (int m=0; m<4; m++) {
				vector<int> elmt;
				for (int l=0; l<3; l++) {
					elmt.push_back(wLines[n][m][l]);
				}
				line.push_back(elmt);
			}
			winLines.push_back(line);
		}
		
	}
	
	virtual void draw(RenderTarget& target, RenderStates states) const {
		// Fills the squares representing the winning line
		vector<vector<int>> winLine(4, vector<int>(3));
		if (this->getWinLine(winLine)) {
			for (int m=0; m<4; m++) {
				Vector2f coord = getCoordByIndices(winLine[m][0], winLine[m][1], winLine[m][2]);
				//cout << winLine[m][0] << winLine[m][1] << winLine[m][2] << endl;
				RectangleShape rect(Vector2f(CELLW, CELLH));
				rect.setPosition(coord);
				rect.setFillColor(Color::Red);
				target.draw(rect, states);
			}
		}
		// Draws the four grids
		for (int i=0; i<4; i++) grids[i].draw(target, states);
	}
	
	int getCell(int i, int j, int k) const {
		return grids[k].getCell(i, j);
	}
	
	void setCell(int i, int j, int k, int val) {
		grids[k].setCell(i, j, val);
	}
	
	int getCellByCoord(Vector2f coord) const {
		for (int k=0; k<4; k++) {
			int c = grids[k].getCellByCoord(coord);
			if (c != -1) return c;
		}
		return -1;
	}
	
	void setCellByCoord(Vector2f coord, int val) {
		for (int k=0; k<4; k++) {
			int c = grids[k].getCellByCoord(coord);
			if (c != -1) grids[k].setCellByCoord(coord, val);
		}
	}
	
	void getIndicesByCoord(int& i, int& j, int& k, Vector2f coord) {
		i = j = k = -1;
		for(int m=0; m<4; m++) {
			int c = grids[m].getCellByCoord(coord);
			if (c != -1) {
				grids[m].getIndicesByCoord(i, j, coord);
				k = m;
			}
		}
	}
	
	Vector2f getCoordByIndices(int i, int j, int k) const {
		return Vector2f(x + i*(CELLW+LINET)+k*185 + LINET, y + j*(CELLH+LINET) + LINET);
	}
	
	// Returns 0 for no win, 1 for win for circles and 2 for win for crosses
	int hasWinLine() const {
		for (int n=0; n<N_WIN_LINES; n++) {
			int val = isCompleteLine(winLines[n]);
			if (val != 0) {
				return val;
			}
		}
		return 0;
	}
	
	int getWinLine(vector<vector<int>>& winLine) const {
		for (int n=0; n<N_WIN_LINES; n++) {
			int val = isCompleteLine(winLines[n]);
			if (val != 0) {
				winLine = winLines[n];
				return val;
			}
		}
		return 0;
	}
	
	int playerWin() const {
		for (int n=0; n<N_WIN_LINES; n++) {
			int val = isCompleteLine(winLines[n]);
			if (val != 0) return val;
		}
		return 0;
	}

};