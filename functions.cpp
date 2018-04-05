#include "functions.h"
#include <stdlib.h>

//Created by Gabriel Jones

std::vector<WaterVehicle> createShips() { //Creates all the ships for the computer, and puts them all into a vector. The actual placement is handled in WaterVehicle
	std::vector<WaterVehicle> ships;
	WaterVehicle aircraftCarrier(5, "Carrier", "C");
	WaterVehicle battleship(4, "Battleship", "B");
	WaterVehicle submarine(3, "Submarine", "S");
	WaterVehicle cruiser(3, "Cruiser", "Cr");
	WaterVehicle destroyer(2, "Destroyer", "D");

	ships.push_back(aircraftCarrier);
	ships.push_back(battleship);
	ships.push_back(submarine);
	ships.push_back(cruiser);
	ships.push_back(destroyer);

	return ships;
}

void placeShips(std::vector<WaterVehicle> &ships, Grid &mainGame) {
	for (int i = 0; i < ships.size(); i++) { //runs the placeship function for each ship on the vector of ships, which adds each ship to the grid object
		ships[i].placeShip(mainGame);
		std::cout << "------------------------------------------------------------------------" << std::endl;
	}
}

bool checkSunk(std::vector<WaterVehicle> &ships) { //The game win condition checker, it will return true if all the ships have been sunk, false if any remain alive.
	for (int i = 0; i < ships.size(); i++) {
		if (!ships[i].isSunk())
			return false;
	}
	return true;
}

void displayShips(std::vector<WaterVehicle> ships) { //displays the contents of all the ships
	for (int i = 0; i < ships.size(); i++)
		std::cout << ships[i] << std::endl;
}

int charToInt(char letters) { //used for getting the integer value from a char to access on the grid
	char list[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	for (int i = 0; i < 10; i++) {
		if (list[i] == letters) {
			return i + 1;
		}
	}
	return -1;
}

char intToChar(int number) { //used for displaying shots properly in the format A1, B2..
	char list[] { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	return list[number-1];

}