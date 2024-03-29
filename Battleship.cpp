#include <iostream>
#include "Computer.h"
//#include "Human.h"
#include "WaterVehicle.h" //ship class
#include "Cell.h" //individual cell locations
#include "functions.h" //general functions/setup
#include "Grid.h" //actual grid
#include <ctime> //for time(null)

//Created by Gabriel Jones

//note to self, grid operates on a 0-9 scale, but displays are 1-10

int main()
{
	srand(time(NULL)); //seed the random

	//groooovy graphics
	//ripped from http://ascii.co.uk/art/battleship
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << " _           _   _   _           _     _" << std::endl;
	std::cout << "| |         | | | | | |         | |   (_) " << std::endl;
	std::cout << "| |__   __ _| |_| |_| | ___  ___| |__  _ _ __ " << std::endl;
	std::cout << "| '_ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ " << std::endl;
	std::cout << "| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |" << std::endl;
	std::cout << "|_.__/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/" << std::endl;
	std::cout << "                                        | |   " << std::endl;
	std::cout << "By Gabriel Jones                        |_|   " << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	
	bool playAgain = true; 
	while (playAgain) { //if player decides they want to play again after they win/lose
		playAgain = false;

		std::cout << "Welcome to BattleShip!" << std::endl;
		std::cout << "Here are the rules:" << std::endl;
		std::cout << "Each player will take turn firing at each other's 10x10 grid by typing the x coordinate along with the y coordinate." << std::endl;
		std::cout << "X coordinates are written in letters A-J, and y coordinates are written in 1-10." << std::endl;
		std::cout << "Each player gets 5 ships, and the goal of each player is to destroy all 5 of the other player's." << std::endl;
		std::cout << "Whenever you fire a shot, you will get feedback on whether it was a hit or a miss as well as the shot showing a a hit or miss on your top grid." << std::endl;
		std::cout << "Any time you hit another player's ship, you automatically get another turn to try and hit the ship again." << std::endl;
		std::cout << "If you manage to kill one of the other player's ships, it will be displayed in your ship status bar below. Conversely, you can see what ships the enemy has killed." << std::endl;
		std::cout << "You can also view the enemy's shots on your bottom grid as well as the placement of your own ships." << std::endl;
		std::cout << "Placement of your own ships can be changed by editing the 'userShips.csv' file." << std::endl;
		std::cout << "Good luck! You win once you've destroyed all of the other player's ships." << std::endl;
		std::cout << std::endl;
		std::cout << "Simple game notation:" << std::endl;
		std::cout << "X = hit, M = miss." << std::endl;
		std::cout << "C = carrier piece, B = battleship piece, Cr = cruiser piece, S = submarine piece, D = destroyer piece." << std::endl;
		std::cout << "Would you like to start a new game? Type yes if so." << std::endl;

		//This little buffer before the game actually starts is just so the player isn't immediately greeted with the game without an explanation of what's going on.
		std::string answer;
		getline(std::cin, answer);

		//End they game if they don't want to play.
		if (answer != "yes") {
			std::cout << "Exiting the game..." << std::endl;
			break;
		}
		
		Human mainPlayer;

		Computer cpu;

		bool winner = false;
		bool whoTurn = true; //true for player, false for cpu

		while (!winner && !mainPlayer.getQuitGame()) { //This will run until a player wins the game or the user quits.
			if (whoTurn) {
				if (mainPlayer.takeTurn(cpu)) { //Taketurn will return true if the player/computer won on that current turn
					winner = true;
				}
				whoTurn = !whoTurn; //If they didn't end up winning, flip the player taking the turn
			}
			else {
				if (cpu.takeTurn(mainPlayer)) {
					winner = true;
				}
				whoTurn = !whoTurn;
			}
		}

		if (mainPlayer.getQuitGame()) { //If the player quit show them the computer's current grids.
			std::cout << "Here are the computer's grids:" << std::endl;
			cpu.displayGrids();
		}

		//Continue the while loop if they want to play again
		std::cout << "The game is finished." << std::endl;
		std::cout << "Would you like to play again? Type yes if so." << std::endl;
		std::string playAgains;
		getline(std::cin, playAgains);
		if (playAgains == "yes") {
			playAgain = true;
		}
	}
    return 0;
}

