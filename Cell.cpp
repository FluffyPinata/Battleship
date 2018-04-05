#include "Cell.h"

//Created by Gabriel Jones

Cell::Cell() {
	cellX = 0;
	cellY = 0;
	isHit = false;
	cellInfo = "~";
}

Cell::Cell(int _x, int _y) { //Constructor for when you know where you want to put the cell, initialised in the grid.
	cellX = _x;
	cellY = _y;
	isHit = false;
	cellInfo = "~";
}

void Cell::displayCell() {
	//when displaying the x value of a cell it's truly an int but we change it to char since that's how the original game works
	char letters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' }; //only ever 0-9 for cellx and celly
	std::cout << letters[cellX] << cellY+1 << std::endl;

}

void Cell::hitCell() {
	//if this cell gets hit by a torpedo update it to be hit
	//std::cout << "Hit cell ";
	//this->displayCell();
	if (cellInfo != "~")//means you hit a ship
		cellInfo = "X";
	else
		cellInfo = "M";
	isHit = true;
}

void Cell::setCellInfo(std::string _info) {
	//in case we need to change what the cell displays
	cellInfo = _info;
}