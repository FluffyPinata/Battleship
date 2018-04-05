#ifndef SHIP_
#define SHIP_

#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"
#include "Grid.h"
#include <iostream>

//Created by Gabriel Jones

//This is the class for creating a ship on the game
//It will accept a starting position, a name, an abbreviation (for displaying), the orientation, whether it's sunk or not, and the cell locations the ship occupies on the grid
//The main driving functions are placeShip, which will get the starting location and orienation and determine if a ship can be placed there on the grid
//As well as isSunk, which will determine if a ship is sunk based on if the ship's cell locations are hit

class WaterVehicle {
private:
	std::string shipName;
	std::string shipAbbreviation; //for what the grid will display as you play
	int shipLength;
	int shipX, shipY; //starting position
	bool horizontal; //if true, ship is horiztonal, if false, vertical.
	bool sunk; //keeps track if the ship got sunk when hit
	std::vector<Cell> shipLocations; //actual cell locations of each ship
public:
	WaterVehicle();
	WaterVehicle(int _shipLength, std::string _shipName, std::string _shipAbbreviation);
	std::string getShipAbbreviation() { return shipAbbreviation; }
	std::string getShipName() { return shipName; }
	bool getOrientation() { return horizontal; }
	void setStartingPosition();
	void setStartingPosition(int _x, int _y);
	void setOrientation();
	void setOrientation(bool _horizontal);
	void verifyGoodPosition(Grid &mainGame);
	bool verifyGoodPosition(Grid &mainGame, int _shipX, int _shipY, bool _horizontal);
	void placeShip(Grid &mainGame); //makes use of 3 previous functions
	bool placeShip(Grid &mainGame, int _shipX, int _shipY, bool _horizontal);
	std::vector<Cell> getShipLocations() const { return shipLocations; }
	void setShipLocations(std::vector<Cell> _shipLocations) { shipLocations = _shipLocations; }
	bool isSunk();
	friend std::ostream & operator<<(std::ostream &os, const WaterVehicle wV);
};

#endif
