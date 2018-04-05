#ifndef _CELL
#define _CELL

#include <iostream>
#include <string>

//Created by Gabriel Jones

//Think of this cell as an object to store the information of an individual place on the grid (ie A1 or G7).
//It will save where it is on the grid as well as what ship may be currently occupying it.
//It also saves if it got hit by a torpedo.

class Cell {
private:
	int cellX, cellY;
	bool isHit;
	std::string cellInfo;
public:
	Cell();
	Cell(int _x, int _y);
	int getX() const { return cellX; }
	int getY() const { return cellY; }
	void setX(int _x) { cellX = _x; }
	void setY(int _y) { cellY = _y; }
	bool getIsHit() const { return isHit; }
	std::string getCellInfo() { return cellInfo; }
	void displayCell();
	void hitCell();
	void setCellInfo(std::string _info);
};

#endif