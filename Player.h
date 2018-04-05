#ifndef PLAYER_H
#define PLAYER_H

//Created by Gabriel Jones

#include "Grid.h"
#include "WaterVehicle.h"
#include "functions.h"
#include <fstream> // for infile
#include <sstream>

class Player {
protected:
	std::vector<WaterVehicle> ships;
	Grid ownGrid = Grid(10,10); //grid user can look at to see what ships are getting hit
	Grid attackingGrid = Grid(10,10); //grid player fires shots at and gets feedback

public:
	Player();
};



#endif