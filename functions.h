#ifndef FUNCTIONS_
#define FUNCTIONS_

#include <iostream>
#include "WaterVehicle.h"
#include "Cell.h"

//Created by Gabriel Jones

//These are the general functions for the program.
//They handle create the ships and the main game (grid), which end up getting passed through these functions to be manipulated.
//Most importantly the ships constantly have their values updated by being passed by reference, such as where they are on the grid or checking if they got hit by torpedos

std::vector<WaterVehicle> createShips();
void placeShips(std::vector<WaterVehicle> &ships, Grid &mainGame); //Main driver for game set up

//These deal with firing 15 torpedos and checking if any ships got sunk
bool checkSunk(std::vector<WaterVehicle> &ships);
void displayShips(std::vector<WaterVehicle> ships);
int charToInt(char letter); 
char intToChar(int number);


#endif