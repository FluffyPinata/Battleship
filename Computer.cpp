#include "Computer.h"
//#include "Human.h"

//Created by Gabriel Jones

Computer::Computer() {
	killingAShip = false; 
	this->generateShips(); //place down all of its ships
}

void Computer::displayGrids() {
	//This will display the two computer grids, only used at the end if the player decides to quit prematurely.
	std::cout << "====================================COMPUTER======================================" << std::endl;
	attackingGrid.displayGrid();
	std::cout << "==================================================================================" << std::endl;
	ownGrid.displayGrid();
}

void Computer::generateShips() {
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Making computer ships..." << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	//Next two functions can be found in 'functions.cpp'
	ships = createShips(); //creates all 5 of the computer's ships and puts them in a vector.
	//Random gens values for starting ship locations and orientations, and places them on the computer's ship grid.
	placeShips(ships, ownGrid);
}

bool Computer::takeTurn(Human &human) {

	//just write out the steps, would help a lot.
	makeRandomMove(human);
	editGridsWithMove(human);

	if (hitShip(human)) {
		prevX = shipX;
		prevY = shipY;
		findValidDirection(human);
		while (stepDirection(human)) {
			
		}
	}
	return false;

	

}

void Computer::makeRandomMove(Human human) {
	//This function will loop until it can pick a valid random move
	//This just means anything that hasn't been hit yet
	bool validInput = false;
	while (!validInput) {
		validInput = true;

		shipX = rand() % 10 + 1;
		shipY = rand() % 10 + 1;

		if (human.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "M" || human.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "X") {
			validInput = false;
		}
	}
}

void Computer::editGridsWithMove(Human &human) { //Edits both the human's ships grid and computer's attack grid with the move.
	human.ownGrid.grid[shipY - 1][shipX - 1].hitCell();
	attackingGrid.grid[shipY - 1][shipX - 1].setCellInfo(human.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo());
}

void Computer::pickRandomDirection() { //Picks any of the 4 directions at random
	int randDirection = rand() % 4;
	if (randDirection == 0)
		currentDirection = north;
	else if (randDirection == 1)
		currentDirection = east;
	else if (randDirection == 2)
		currentDirection = south;
	else if (randDirection == 3)
		currentDirection = west;
}

void Computer::findValidDirection(Human &human) {
	//where it starts to guess the next place to hit
	bool goodInput = false;
	while (!goodInput) { //repeats until the random direction found was valid
		goodInput = true;
		int tempX = shipX; //used for saving the coordinate values if we need to remake them
		int tempY = shipY;

		pickRandomDirection();

		//makes the next move based on the direction picked
		if (currentDirection == north)
			shipY--;
		else if (currentDirection == east)
			shipX++;
		else if (currentDirection == south)
			shipY++;
		else if (currentDirection == west)
			shipX--;

		if (shipX > 10 || shipX < 1 || shipY > 10 || shipY < 1) { //steps out of bounds
			shipX = tempX;
			shipY = tempY;
			//std::cout << "Out of bounds" << std::endl;
			goodInput = false;
		}
		else if (human.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "M" || human.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "X") { //Attacking a spot that's already been hit
			shipX = tempX;
			shipY = tempY;
			//std::cout << "Trying to hit a space it already has." << std::endl;
			goodInput = false;
			//The one problem with this function is that it can potentially get trapped if there isn't any place to go
		}
		//Revert the values back now that it's found a good direction
		shipX = tempX;
		shipY = tempY;
	}
}

bool Computer::stepDirection(Human &human) { //Make attacks in the specified direction until it hits a wall or gets a miss.
	if (currentDirection == north) {
		shipY--;
		if (shipY < 1) { //Bounds checker for if the direction sends it into a wall
			currentDirection = south; 
			return false;
		}
		editGridsWithMove(human); //Edit the move onto the grid
		if (!hitShip(human)) { //If it missed, stop attacking in that direction
			return false;
		}
	}
	else if (currentDirection == east) {
		shipX++;
		if (shipX > 10) {
			currentDirection = west;
			return false;
		}
		editGridsWithMove(human);
		if (!hitShip(human)) {
			return false;
		}
	}
	else if (currentDirection == south) {
		shipY++;
		if (shipY > 10) {
			currentDirection = north;
			return false;
		}
		editGridsWithMove(human);
		if (!hitShip(human)) {
			return false;
		}
	}
	else if (currentDirection == west) {
		shipX--;
		if (shipX < 1) {
			currentDirection = east;
			return false;
		}
		editGridsWithMove(human);
		if (!hitShip(human)) {
			return false;
		}
	}
	//std::cout << currentDirection << std::endl;
	//std::cout << shipX << ":" << shipY << std::endl;
	return true;
}

bool Computer::hitShip(Human &human) { //This function checks if the attack it's making ends up being a hit or not
	//This function will return true if it hit a ship, and false if it missed
	bool hitShip = false;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Computer attacking " << intToChar(shipX) << shipY << "!" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	for (int i = 0; i < human.ships.size(); i++) { //loop through all the ships until we find the cell that we hit that had a ship
		std::vector<Cell> copyShipLocations = human.ships[i].getShipLocations(); //get the locations of each ship

		for (int j = 0; j < copyShipLocations.size(); j++) { //cycle through those locations
			if (copyShipLocations[j].getX() == shipX && copyShipLocations[j].getY() == shipY) { //edit that cell to be hit if we found that it got hit
				copyShipLocations[j].hitCell();
				if (copyShipLocations[j].getCellInfo() == "X") {//check for if the attack was a hit
					killingAShip = true;
					hitShip = true;
					std::cout << "------------------------------------------------------------------------" << std::endl;
					std::cout << "Computer got a hit! It gets to move again!." << std::endl;
					std::cout << "------------------------------------------------------------------------" << std::endl;
					if (human.ships[i].isSunk()) { //check if that hit ended up sinking that particular ship
						std::cout << "------------------------------------------------------------------------" << std::endl;
						std::cout << "Computer sunk your " << human.ships[i].getShipName() << "!" << std::endl;
						std::cout << "------------------------------------------------------------------------" << std::endl;
						killingAShip = false;
					}
				} 
			}
		}

		human.ships[i].setShipLocations(copyShipLocations); //set the edited cell locations

	}
	if (!hitShip) { //If it ended up missing, display so.
		std::cout << "------------------------------------------------------------------------" << std::endl;
		std::cout << "Computer missed! It's now your turn!." << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;
	}
	return hitShip;
}