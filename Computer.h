#ifndef COMPUTER_H
#define COMPUTER_H

//Created by Gabriel Jones

#include "Player.h"

class Computer; //Originally I had two header files, one for Human and Computer, but I ran into an issue with circular dependency. So now it's all in 1.

class Human : public Player { //inherits from Player
	friend class Computer; //so it can access enemy's grid
private:
	bool quitGame; // used for keeping track of if the player has quit the game or not
public:
	Human();
	void readShips(); //read in from csv
	void displayGrids();
	bool takeTurn(Computer &enemy);
	void displayShipStatus(Computer &enemy);
	bool getQuitGame() { return quitGame; }
};

class Computer : public Player { //inherits from Player
	friend class Human; //so it can access enemy's grid
private:
	enum Direction { north, east, south, west }; //used for picking direction to attack whenever it successfully lands a hit
	Direction currentDirection;
	int shipX;
	int shipY;
	int prevX;
	int prevY;
	bool killingAShip; //Originially I was planning on having a more intelligent AI, but unfortunately I couldn't get it to work satisfactory. This would've kept track of if it had killed the ship it was currently attacking.
	bool horizShip;
public:
	Computer();
	void generateShips(); //random gen ship locations
	void makeRandomMove(Human human); //fire random shot
	void editGridsWithMove(Human &human); //edit the enemy's grid and computer's attack grid with the shot
	bool hitShip(Human &human); //check if the shot hit a ship, and if it did, edit the player's ships to reflect that
	void pickRandomDirection(); //for choosing a random direction to attack next after a hit.
	void findValidDirection(Human &human); //checks if that random direction is possible to fire towards
	bool stepDirection(Human &human); //will fire 1 shot in the specified direction, until it either reaches a border or a space that's already been hit. will return true if the shot was a hit
	void displayGrids(); //displays attack and own grid
	bool takeTurn(Human &human); //runs all the logic for a turn based on if it hits a ship or not
};

#endif 
