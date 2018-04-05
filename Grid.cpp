#include "Grid.h"
#include <stdlib.h>

//Created by Gabriel Jones
//Very slightly modified so it can support cells rather than ints

//Default contructor, if a height and length is either unknown or can't be passed for whatever reason.
//This is used to create the initial grid which later gets copied. Essentially this is the type of grid a user can directly make.
//Asks the user for both the height and length and saves it the grid.
Grid::Grid() {
	int _length, _height;
	std::cout << "Please enter the grid's height." << std::endl;
	std::cin >> _height;
	std::cout << "Please enter the grid's length." << std::endl;
	std::cin >> _length;
	length = _length;
	height = _height;
	this->createGrid();
}

//If the length and height are already known, you can use this to make a grid with those specific values.
//Useful for if you want to copy another grid's size, since you can just pass that one's length and height.
Grid::Grid(int _height, int _length) { 
	height = _height;
	length = _length;
	this->createGrid();
}

//This is the function that actually 'makes' the grid. It relies on the length and height being read already else it'll make nothing.
//The function resize will strech the vector to be a specific size, specifically the first vector being number of rows and the second being the length of them.
//The height is used to create the leftmost side of the grid, 1xHeight.
//Each of these elements on the leftmost column is then given a row of size Lengthx1, filling out the grid.
void Grid::createGrid() {
	grid.resize(height);
	for (int i = 0; i < height; i++) {
		grid[i].resize(length);
	}

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < height; j++) {
			grid[i][j] = Cell(i, j);
		}
	}
}

//Displays the chars for the x coordinates first, then loops through the contents of each cell on the grid.
void Grid::displayGrid() { 
	std::cout << "\t" << "A\tB\tC\tD\tE\tF\tG\tH\tI\tJ\t" << std::endl << std::endl;
	for (int i = 0; i < height; i++) {
		std::cout << i + 1 << "\t"; //Number to mark the row 
		for (int j = 0; j < length; j++) {
			std::cout << grid[i][j].getCellInfo() << "\t"; //Contents of the row
		}
		std::cout << std::endl << std::endl;
	}
}
