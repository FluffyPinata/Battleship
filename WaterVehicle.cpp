#include "WaterVehicle.h"

//Created by Gabriel Jones

WaterVehicle::WaterVehicle() { //default constructor, just places the ship at  0,0 with no length until you set it
	shipLength = 0;
	shipX = 0;
	shipY = 0;
	shipName = "";
	shipAbbreviation = "";
	horizontal = true;
	sunk = false;

}

WaterVehicle::WaterVehicle(int _shipLength, std::string _shipName, std::string _shipAbbreviation) { //constructor if you already know what kinds of ships you want to make, such as the original 5
	shipLength = _shipLength;
	shipName = _shipName;
	shipAbbreviation = _shipAbbreviation;
	shipX = 0;
	shipY = 0;
	horizontal = true;
	sunk = false;
}

void WaterVehicle::setStartingPosition() { //randomly generated
	shipX = rand() % 10 + 1;
	shipY = rand() % 10 + 1;
	/*std::cout << "What would you like the starting x position for the " << shipName << " to be?" << std::endl;
	std::cin >> shipX;
	std::cout << "What would you like the starting y position for the " << shipName << " to be?" << std::endl;
	std::cin >> shipY;*/
}

void WaterVehicle::setStartingPosition(int _x, int _y) { //known value
	shipX = _x;
	shipY = _y;
}

void WaterVehicle::setOrientation() { //randomly generated
	int hOrZ = rand() % 2;
	if (hOrZ == 0)
		horizontal = true;
	else
		horizontal = false;
}

void WaterVehicle::setOrientation(bool _horizontal) { //known value
	horizontal = _horizontal;
}

void WaterVehicle::verifyGoodPosition(Grid &mainGame) { //checks whether a legal move is made, we also pass in the Grid here so we can edit the cells when we place the ships
	bool goodPosition = false;
	while (!goodPosition) { //This will loop until a valid postion is made for the ship. 
		goodPosition = true; //Assume a correct position gets picked until specified otherwise

		//Get the requested ship location and orientation.
		this->setStartingPosition();
		this->setOrientation();

		//this checks if it crosses over a border
		if (horizontal) {
			if (shipX + (shipLength - 1) > 10) { //trying to put a ship too close to the right side will fail horizontally, because those cells don't even exist
				//std::cout << "Specified ship placement reaches over a border, please try a different set of coordinates or orientation." << std::endl;
				goodPosition = false;
			}
		}
		else {
			if (shipY + (shipLength - 1) > 10) { //similarly, trying to place a vertical ship too close to the bottom fails as well
				//std::cout << "Specified ship placement reaches over a border, please try a different set of coordinates or orientation." << std::endl;
				goodPosition = false;
			}
		}

		if (goodPosition) { //to make sure the ship isn't over an edge and accessing nonexistant cells
			//this checks for overlapping ships
			for (int i = 0; i < shipLength; i++) { //loop through all possible coordinates for the ship (2-5 in the case of a standard game)
				if (horizontal) { //if it's horizontal it will look at the cells to the right
					if (mainGame.grid[shipY - 1][shipX - 1 + i].getCellInfo() != "~") { //finds a cell that's not blank (i.e, there's a cell with a ship in it)
						//std::cout << "Ship overlaps another at ";
						mainGame.grid[shipY - 1][shipX - 1 + i].displayCell();
						goodPosition = false; //mark as a bad position
					}
				}
				else { //otherwise look at the cells that are down (vertical)
					if (mainGame.grid[shipY - 1 + i][shipX - 1].getCellInfo() != "~") {
						//std::cout << "Ship overlaps another at ";
						mainGame.grid[shipY - 1 + i][shipX - 1].displayCell();
						goodPosition = false;
					}
				}
			}
		}
	} //end while
	std::cout << "Entered ship position is good!" << std::endl;
}

bool WaterVehicle::verifyGoodPosition(Grid &mainGame, int _shipX, int _shipY, bool _horizontal) { //used when values for ship position are known and not random genned
		//Get the requested ship location and orientation.
		this->setStartingPosition(_shipX, _shipY);
		this->setOrientation(_horizontal);

		//this checks if it crosses over a border
		if (horizontal) {
			if (shipX + (shipLength - 1) > 10) { //trying to put a ship too close to the right side will fail horizontally, because those cells don't even exist
				std::cout << "Specified ship placement reaches over a border, please try a different set of coordinates or orientation." << std::endl;
				return false;
			}
		}
		else {
			if (shipY + (shipLength - 1) > 10) { //similarly, trying to place a vertical ship too close to the bottom fails as well
				std::cout << "Specified ship placement reaches over a border, please try a different set of coordinates or orientation." << std::endl;
				return false;
			}
		}

							//this checks for overlapping ships
			for (int i = 0; i < shipLength; i++) { //loop through all possible coordinates for the ship (2-5 in the case of a standard game)
				if (horizontal) { //if it's horizontal it will look at the cells to the right
					if (mainGame.grid[shipY - 1][shipX - 1 + i].getCellInfo() != "~") { //finds a cell that's not blank (i.e, there's a cell with a ship in it)
						std::cout << "Ship overlaps another at ";
						mainGame.grid[shipY - 1][shipX - 1 + i].displayCell();
						return false; //mark as a bad position
					}
				}
				else { //otherwise look at the cells that are down (vertical)
					if (mainGame.grid[shipY - 1 + i][shipX - 1].getCellInfo() != "~") {
						std::cout << "Ship overlaps another at ";
						mainGame.grid[shipY - 1 + i][shipX - 1].displayCell();
						return false;
					}
				}
			}
	
	std::cout << "Entered ship position is good!" << std::endl;
	return true;
}

void WaterVehicle::placeShip(Grid &mainGame) { //verifies the starting location is good then creates all the cells for each part of the ship
	this->verifyGoodPosition(mainGame); //this will only run once the locations are verified as being empty and on the grid
	for (int i = 0; i < shipLength; i++) { //Add the cells of each part of the ship
		if (horizontal) { // Just a note, since it starts with columns for the grid matrix, we need to flip the y and x when we access a grid point, as opposed to what we usually would think
			Cell tempCell(shipX + i, shipY); //create the cell that we end up putting in both the grid and the ship object itself
			tempCell.setCellInfo(shipAbbreviation);
			//tempCell.displayCell();
			mainGame.grid[shipY-1][shipX + i - 1] = tempCell;
			shipLocations.push_back(tempCell);
		}
		else { //vertical, as opposed to horizonal, goes further down for how long the ship is
			Cell tempCell(shipX, shipY + i);
			tempCell.setCellInfo(shipAbbreviation);
			//tempCell.displayCell();
			mainGame.grid[shipY + i - 1][shipX-1] = tempCell; 
			shipLocations.push_back(tempCell);
		}
	}
	//mainGame.displayGrid(); debuggin line
}

bool WaterVehicle::placeShip(Grid &mainGame, int _shipX, int _shipY, bool _horizontal) { //verifies the starting location is good then creates all the cells for each part of the ship (this is if you already know the inputs)
	if (this->verifyGoodPosition(mainGame, _shipX, _shipY, _horizontal)) { //this will only run once the locations are verified as being empty and on the grid
		for (int i = 0; i < shipLength; i++) { //Add the cells of each part of the ship
			if (horizontal) { // Just a note, since it starts with columns for the grid matrix, we need to flip the y and x when we access a grid point, as opposed to what we usually would think
				Cell tempCell(shipX + i, shipY); //create the cell that we end up putting in both the grid and the ship object itself
				tempCell.setCellInfo(shipAbbreviation);
				//tempCell.displayCell();
				mainGame.grid[shipY - 1][shipX + i - 1] = tempCell;
				shipLocations.push_back(tempCell);
			}
			else { //vertical, as opposed to horizonal, goes further down for how long the ship is
				Cell tempCell(shipX, shipY + i);
				tempCell.setCellInfo(shipAbbreviation);
				//tempCell.displayCell();
				mainGame.grid[shipY + i - 1][shipX - 1] = tempCell;
				shipLocations.push_back(tempCell);
			}
		}
		//mainGame.displayGrid(); debuggin line
		return true;
	}
	return false;
}


bool WaterVehicle::isSunk() {
	for (int i = 0; i < shipLength; i++) { //checks each of the cells in the ship to see if any of them got hit
		if (!shipLocations[i].getIsHit()) { //shorthand for saying if a location didn't get hit that means the whole ship isn't sunk
			sunk = false;
			return false;
		}
	}
	sunk = true;
	return true;
}

std::ostream & operator<<(std::ostream &os, const WaterVehicle wV) { //outputs all the data for any one ship, not too much to say
	std::string orientation = "horizontal";
	std::string sunkStatus = "is not sunk";
	if (!wV.horizontal)
		orientation = "vertical";
	if (wV.sunk)
		sunkStatus = "is sunk";
	return os << wV.shipName << "|| Ship Length:\t" << wV.shipLength << "|| Starting Location\t" << wV.shipX << "," << wV.shipY << "|| Orientation\t" << orientation << "|| Sunk Status:\t" << sunkStatus;
}

