
#include "Table.h"
#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>

using namespace std;

void Table::drawBoard(Dealer* d){
	// using a stringstream rather than a string to make making the banner easier
	stringstream messageString;

	// various variable declarations
	char key;
	char key2;
	int cardX = 0;
	int cardY = 0;
	//int suit = 0;
	//int number = 0;


	// Player 1
	gameDisplay.drawBox(47, 6, 13, 3, 0);		// Money
	mvprintw(7,48,"Money");						// Need to refresh
	gameDisplay.drawBox(47, 8, 13, 3, 0);		// Last action
	mvprintw(9,48,"Action");					// Need to refresh
	gameDisplay.displayCard(47,2,0,0, A_BOLD);
	gameDisplay.displayCard(54,2,0,0, A_BOLD);
	
	// Player 2
	gameDisplay.drawBox(10, 11, 13, 3, 0);		// Money
	mvprintw(12,11,"Money");					// Need to refresh
	gameDisplay.drawBox(10, 13, 13, 3, 0);		// Last action
	mvprintw(14,11,"Action");					// Need to refresh
	gameDisplay.displayCard(10,7,0,0, A_BOLD);
	gameDisplay.displayCard(17,7,0,0, A_BOLD);

	// Player 3
	gameDisplay.drawBox(10, 23, 13, 3, 0);		// Money
	mvprintw(24,11,"Money");					// Need to refresh
	gameDisplay.drawBox(10, 25, 13, 3, 0);		// Last action
	mvprintw(26,11,"Action");					// Need to refresh
	gameDisplay.displayCard(10,19,0,0, A_BOLD);
	gameDisplay.displayCard(17,19,0,0, A_BOLD);

	// Player 4    HUMAN
	gameDisplay.drawBox(35, 33, 13, 3, 0);		// Money
	mvprintw(34,36,"Money");					// Need to refresh
	gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
	mvprintw(36,36,"Action");					// Need to refresh
	gameDisplay.displayCard(35,29,rand()%5,rand()%15, A_BOLD);
	gameDisplay.displayCard(42,29,rand()%5,rand()%15, A_BOLD);

	// Player 5
	gameDisplay.drawBox(78, 23, 13, 3, 0);		// Money
	mvprintw(24,79,"Money");					// Need to refresh
	gameDisplay.drawBox(78, 25, 13, 3, 0);		// Last action
	mvprintw(26,79,"Action");					// Need to refresh
	gameDisplay.displayCard(78,19,0,0, A_BOLD);
	gameDisplay.displayCard(85,19,0,0, A_BOLD);

	// Player 6
	gameDisplay.drawBox(78, 11, 13, 3, 0);		// Money
	mvprintw(12,79,"Money");					// Need to refresh
	gameDisplay.drawBox(78, 13, 13, 3, 0);		// Last action
	mvprintw(14,79,"Action");					// Need to refresh
	gameDisplay.displayCard(78,7,0,0, A_BOLD);
	gameDisplay.displayCard(85,7,0,0, A_BOLD);

	// Flop
	mvprintw(15,51,"Flop");
	gameDisplay.displayCard(38,16,rand()%5,rand()%15, A_BOLD);
	gameDisplay.displayCard(44,16,rand()%5,rand()%15, A_BOLD);
	gameDisplay.displayCard(50,16,rand()%5,rand()%15, A_BOLD);
	gameDisplay.displayCard(56,16,rand()%5,rand()%15, A_BOLD);
	gameDisplay.displayCard(62,16,rand()%5,rand()%15, A_BOLD);
	gameDisplay.drawBox(46, 23, 15, 3, 0);		// Money in Side Pot
	mvprintw(24,47,"Side Pot");
	gameDisplay.drawBox(46, 21, 15, 3, 0);		// Money in Pot
	mvprintw(22,47,"Main Pot");

	
	// Choices
	mvprintw(34,74,"Options");

	gameDisplay.drawBox(50, 28, 19, 6, 0);		// Top Left
	mvprintw(30,55,"Check/Call");
	gameDisplay.drawBox(50, 35, 19, 6, 0);		// Bottom Left
	mvprintw(37,55,"Free Money");
	gameDisplay.drawBox(69, 28, 18, 6, 0);		// Top Middle
	mvprintw(30,75,"Raise");
	gameDisplay.drawBox(69, 35, 18, 6, 0);		// Bottom Middle
	mvprintw(37,75,"ALL IN");
	gameDisplay.drawBox(87, 28, 19, 6, 0);		// Top Right
	mvprintw(30,94,"Fold");
	gameDisplay.drawBox(87, 35, 19, 6, 0);		// Bottom Right
	mvprintw(37,94,"Quit");

	int keynew = 0;
	int bet = 0;
	bool isTurn = true;

	gameDisplay.captureInput(); //flushes display to screen
}

Move Table::getUserMove(){
	return FOLD;
}

int Table::getUserValue(){
	return 100;
}
