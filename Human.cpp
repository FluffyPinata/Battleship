//#include "Human.h"
#include "Computer.h"

//Created by Gabriel Jones

Human::Human() {
	this->readShips(); //read in all the ships from the file and place them if it can
	quitGame = false;
}


void Human::displayGrids() {
	std::cout << "=====================================HUMAN========================================" << std::endl;
	attackingGrid.displayGrid();
	std::cout << "==================================================================================" << std::endl;
	ownGrid.displayGrid();
}


void Human::readShips() {
	std::ifstream infile("userShips.csv");
	//junk getline to skip the first line of the file
	std::string junk;
	getline(infile, junk);
	std::string line;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Making human ships..." << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	while (getline(infile, line)) { //get the line
		std::stringstream ss(line); //feed the line into a stream, which we can access the broken up parts from.

		std::string name, abbreviation, startPosition, orientation;

		//Parse each part of the ss into variables (all type string), by commas
		getline(ss, name, ',');
		getline(ss, startPosition, ',');
		getline(ss, orientation, ',');


		int actualLength; 

		char letterX = startPosition[0]; //the first part of the input will always be 1 letter, so we can just access the first index
		std::string letterY = startPosition.substr(1); //this is purely in case the starting position is chosen to be 10, otherwise we'd just read into a char

		//Convert both the letters into integer values we can use
		int shipX = charToInt(letterX);
		int shipY = stoi(letterY);

		//Default the orientation to horizontal
		bool horizontal = true;
		if (orientation == "V")
			horizontal = false;

		//Check the name of the ship that was read in and assign the appropriate abbreviation and length.
		if (name == "Carrier") {
			abbreviation = "C";
			actualLength = 5;
		}
		else if (name == "Battleship") {
			abbreviation = "B";
			actualLength = 4;
		}
		else if (name == "Cruiser") {
			abbreviation = "Cr";
			actualLength = 3;
		}
		else if (name == "Submarine") {
			abbreviation = "S";
			actualLength = 3;
		}
		else if (name == "Destroyer") {
			abbreviation = "D";
			actualLength = 2;
		}
		
		//Create the ship
		WaterVehicle tempShip(actualLength, name, abbreviation);


		if (tempShip.placeShip(this->ownGrid, shipX, shipY, horizontal)) { //this makes use of the overloaded placeships function which instead works with known inputs as opposed to randomly genned ones
			std::cout << "Successfully placed " << name << std::endl;
		}
		else {
			std::cout << "Couldn't place " << name << std::endl; //if it can't place it successfully, it will just make up a random location so you can play anyways
			std::cout << "Generating random location..." << std::endl;
			tempShip.placeShip(this->ownGrid); //generate a random location to put it
		}

		std::cout << "------------------------------------------------------------------------" << std::endl;
		//put it in the vector for sunk/hit calculations later
		ships.push_back(tempShip);
	}
}

bool Human::takeTurn(Computer &enemy) {

	bool hitAShip = true;
	while (hitAShip) { //This will run again if the player hits one of the enemy's ships, meaning they get an extra turn.
		hitAShip = false; //By default they didn't hit a ship on this turn.
		this->displayGrids(); 
		this->displayShipStatus(enemy);

		int shipX;
		int shipY;
		bool validInput = false; 
		while (!validInput) { //This will run while the input isn't good. Inputs get flagged if they're bad so it will go back to getting the input again.
			validInput = true;
			std::cout << "Please make a guess in the form of LETTERNUMBER (example A8), to fire at a space on the opponent's board. Alternatively you can press Q to quit." << std::endl;
			std::string guess;

			

			getline(std::cin, guess);

			if (guess == "Q" || guess == "q") { //Allows the player to exit the game at any time if they choose.
				std::cout << "Quitting the game..." << std::endl;
				quitGame = true;
				return false;
			}

			if (std::cin.fail() || (guess.length() != 2 && guess.length() != 3)) { //First check to ensure input is a valid length (and it's actually a string!)
				validInput = false;
				std::cout << "That input couldn't be read, make sure it's in the valid format of LETTERNUMBER." << std::endl;
			}
			else {
				//read in the guess
				char letterX = guess[0]; //the first part of the input will always be 1 letter, so we can just access the first index
				std::string letterY = guess.substr(1); //this is purely in case the starting position is chosen to be 10, otherwise we'd just read into a char
															   //Convert both the letters into integer values we can use
				shipX = charToInt(letterX);

				try { //this is to catch if the user for whatever reason inputs the y coordinate as not a number (ex Att)
					shipY = stoi(letterY);
				}
				catch (std::invalid_argument) {
					validInput = false;
					std::cout << "Couldn't read the second part (1-10) of your input correctly. Make sure it's purely an number." << std::endl;
				}

				if (validInput) { //This will make sure it doesn't try to use a bad input if it previously failed for accessing the grid.
					if (shipY > 10 || shipY < 1 || shipX > 10 || shipX < 0) { //So you don't try A30 or X1
						validInput = false;
						std::cout << "Input must be within 1-10 and A-J." << std::endl;
					}
					else if (enemy.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "M" || enemy.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "X") { //Prevents duplicate attacks
						validInput = false;
						std::cout << "You've already attacked that cell, please choose another." << std::endl;
					}
				}
			}

		}
		

		//firstly edit the displays on both the grids
		enemy.ownGrid.grid[shipY - 1][shipX - 1].hitCell(); //grid is in reverse based on our input, so we need to flip x and y
		attackingGrid.grid[shipY - 1][shipX - 1].setCellInfo(enemy.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo()); //set the info to be what the enemy grid shows

		//make sure we edit the ships to be edited as hit as well.

		std::cout << "------------------------------------------------------------------------" << std::endl;
		std::cout << "You attacked " << intToChar(shipX) << shipY << "!" << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;

		if (enemy.ownGrid.grid[shipY - 1][shipX - 1].getCellInfo() == "X") {
			hitAShip = true;
			std::cout << "------------------------------------------------------------------------" << std::endl;
			std::cout << "You hit a ship! You can take another turn!" << std::endl;
			std::cout << "------------------------------------------------------------------------" << std::endl;
			for (int i = 0; i < enemy.ships.size(); i++) { //loop through all the ships until we find the cell that we hit that had a ship
				std::vector<Cell> copyShipLocations = enemy.ships[i].getShipLocations(); //get the locations of each ship
				for (int j = 0; j < copyShipLocations.size(); j++) { //cycle through those locations
					if (copyShipLocations[j].getX() == shipX && copyShipLocations[j].getY() == shipY) { //edit that cell to be hit if we found that it got hit
						copyShipLocations[j].hitCell();
					}
				}
				enemy.ships[i].setShipLocations(copyShipLocations); //set the edited cell locations
				//if (enemy.ships[i].isSunk()) { //check if that hit ended up sinking all the ships
				//	std::cout << "You sunk the enemy's " << enemy.ships[i].getShipName() << "!" << std::endl;
				//}
			}
			if (checkSunk(enemy.ships)) { //Checking the win condition to see if you sunk all ships
				std::cout << "------------------------------------------------------------------------" << std::endl;
				std::cout << "You have sunk all the enemy's ships! You have won the game!" << std::endl;
				std::cout << "------------------------------------------------------------------------" << std::endl;
				return true;
			}
		}
		else {
			std::cout << "------------------------------------------------------------------------" << std::endl;
			std::cout << "You missed, now the enemy gets their turn." << std::endl;
			std::cout << "------------------------------------------------------------------------" << std::endl;
			return false;
		}
	}


	//for (int i = 0; i < ships.size(); i++) { //for each ship
	//	std::vector<Cell> newShipLocations; //vector we will add the cells that got hit

	//	for (int j = 0; j < copyShipLocations.size(); j++) { //loop through each cell in the current ship's locations

	//		for (int k = 0; k < torpedoShots.size(); k++) { //Check if the cell/location was one of the random ones picked to be hit by comparing it against each torpedo shot
	//			if (copyShipLocations[j].getX() == torpedoShots[k].getX() && copyShipLocations[j].getY() == torpedoShots[k].getY()) { //if it finds equivalent cells, mark the ship location as being hit
	//				copyShipLocations[j].hitCell();
	//			}
	//		}
	//		newShipLocations.push_back(copyShipLocations[j]); //add that cell regardless of if it was changed or not

	//	}

	//	ships[i].setShipLocations(newShipLocations); //set the ship locations to the duplicate of the original ship locations with them now marked as hit
	//}
}

void Human::displayShipStatus(Computer &enemy) { //Displays the sunk value for each ship after each turn, so the player can keep track of their progress.
	std::cout << "Your Ships:" << "\t\t" << "Computer Ships:" << "\t" << std::endl;
	for (int i = 0; i < ships.size(); i++) {
		std::string sunkStatus = "Alive";
		if (ships[i].isSunk()) {
			sunkStatus = "Sunk";
		}

		std::string sunkStatus1 = "Alive";
		if (enemy.ships[i].isSunk()) {
			sunkStatus1 = "Sunk";
		}
		std::cout << ships[i].getShipName() << ":\t" << sunkStatus << "\t" << enemy.ships[i].getShipName() << ":\t" << sunkStatus1 << std::endl;
	}
}