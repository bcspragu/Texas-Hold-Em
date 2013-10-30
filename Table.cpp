
#include "Table.h"
#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>

using namespace std;

Table::Table(){

}

void Table::drawBoard(Dealer* d){

}

Move Table::getUserMove(){
	return FOLD;
}

int Table::getUserValue(){
	return 100;
}