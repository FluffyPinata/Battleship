#ifndef GRID_
#define GRID_

#include <iostream>
#include <vector>
#include "Cell.h"

//Created by Gabriel Jones


class Grid {
	friend class Computer; //purely so both players can edit their grids easily
	friend class Human;
	friend class WaterVehicle; //so the ships can access the grid when they're being placed
private:
	//Our actual 'grid', is just a vector of vectors. The outside vector will represent the number of rows/height and the inner the length of rows/length.
	std::vector< std::vector<Cell> > grid; //this time however it's of type cell, not int
	//We store these values so we can make the grid itself later
	int height, length;
public:
	Grid();
	Grid(int _height, int _length);
	int getHeight() const { return height; }
	int getLength() const { return length; }
	void createGrid();
	void displayGrid();
};

#endif 