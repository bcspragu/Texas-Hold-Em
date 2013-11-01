/* Title: Project 1 ECE373 Example driver artifact for Display class
 * Author: John Shield
 * Description: Demonstrates Unix Signal capturing and the Display class
 *		functionality.
 *
 * NOTES:
 *      * Requires the terminal (Putty) to be set to UTF-8.
 *      * Does not function when running a screen session.
 */
#include "display.h"
#include "Dealer.h"
#include "User.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>

/* No Header file for this example driver artifact
 * function declaration here instead.
 */
// Signal Subroutine for Window Resize
static void detectResize (int sig); 
// stub artifact for what the game does when the screen resizes
void stub_PrintResize(void); 

// The gameDisplay object is global, because the static signal handler object
// needs to access the dynamic object.
display gameDisplay;

stringstream messageString;
int keynew = 0;
int bet = 0;
bool isTurn = true;

char key;
char key2;
int cardX = 0;
int cardY = 0;
/*
 * This is the main function that starts the driver artifact.
 * This function demonstrates some of the abilities of the Display class
 */
int main(int argc, char* argv[])
{
  signal(SIGWINCH, detectResize); // enable the window resize signal
  // Player 1
  gameDisplay.drawBox(47, 6, 13, 3, 0);		// Money
  mvprintw(7,48,"Money");
  gameDisplay.drawBox(47, 8, 13, 3, 0);		// Last action
  mvprintw(9,48,"Action");
  gameDisplay.displayCard(47,2,0,0, A_BOLD);
  gameDisplay.displayCard(54,2,0,0, A_BOLD);

  // Player 2
  gameDisplay.drawBox(10, 11, 13, 3, 0);		// Money
  mvprintw(12,11,"Money");
  gameDisplay.drawBox(10, 13, 13, 3, 0);		// Last action
  mvprintw(14,11,"Action");
  gameDisplay.displayCard(10,7,0,0, A_BOLD);
  gameDisplay.displayCard(17,7,0,0, A_BOLD);

  // Player 3
  gameDisplay.drawBox(10, 23, 13, 3, 0);		// Money
  mvprintw(24,11,"Money");
  gameDisplay.drawBox(10, 25, 13, 3, 0);		// Last action
  mvprintw(26,11,"Action");
  gameDisplay.displayCard(10,19,0,0, A_BOLD);
  gameDisplay.displayCard(17,19,0,0, A_BOLD);

  // Player 4    HUMAN
  gameDisplay.drawBox(35, 33, 13, 3, 0);		// Money
  mvprintw(34,36,"Money");
  gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
  mvprintw(36,36,"Action");
  gameDisplay.displayCard(35,29,0,0, A_BOLD);
  gameDisplay.displayCard(42,29,0,0, A_BOLD);

  // Player 5
  gameDisplay.drawBox(78, 23, 13, 3, 0);		// Money
  mvprintw(24,79,"Money");
  gameDisplay.drawBox(78, 25, 13, 3, 0);		// Last action
  mvprintw(26,79,"Action");
  gameDisplay.displayCard(78,19,0,0, A_BOLD);
  gameDisplay.displayCard(85,19,0,0, A_BOLD);

  // Player 6
  gameDisplay.drawBox(78, 11, 13, 3, 0);		// Money
  mvprintw(12,79,"Money");
  gameDisplay.drawBox(78, 13, 13, 3, 0);		// Last action
  mvprintw(14,79,"Action");
  gameDisplay.displayCard(78,7,0,0, A_BOLD);
  gameDisplay.displayCard(85,7,0,0, A_BOLD);


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

  //Draw blank community cards
  gameDisplay.displayCard(38,16,0,0, A_BOLD);
  gameDisplay.displayCard(44,16,0,0, A_BOLD);
  gameDisplay.displayCard(50,16,0,0, A_BOLD);
  gameDisplay.displayCard(56,16,0,0, A_BOLD);
  gameDisplay.displayCard(62,16,0,0, A_BOLD);
  Dealer d;
  return 0;
}

void Dealer::dealHands(){
  //Draw blank community cards
  gameDisplay.displayCard(38,16,0,0, A_BOLD);
  gameDisplay.displayCard(44,16,0,0, A_BOLD);
  gameDisplay.displayCard(50,16,0,0, A_BOLD);
  gameDisplay.displayCard(56,16,0,0, A_BOLD);
  gameDisplay.displayCard(62,16,0,0, A_BOLD);
  std::vector<Player*>::iterator pitr;
  //Clear out each user's hand, then deal them a new one
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    if((*pitr) != NULL){
      (**pitr).hand.clear();
    }
  }
  for(int i = 0; i < 2; i++){
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      if((*pitr) != NULL){
        (**pitr).hand.push_back(deck.dealCard());
      }
    }
  }
  gameDisplay.displayCard(35,29,players.front()->hand.front().suit+1,players.front()->hand.front().value+2, A_BOLD);
  gameDisplay.displayCard(42,29,players.front()->hand.back().suit+1,players.front()->hand.back().value+2, A_BOLD);
}
void Dealer::updateValuesOnScreen(){
  char tmpstr[21];

  // Player 1
  gameDisplay.drawBox(47, 6, 13, 3, 0);   // Money
  sprintf(tmpstr, "$%d", players[1]->wallet);
  mvprintw(7,48,tmpstr);
  gameDisplay.drawBox(47, 8, 13, 3, 0);   // Last action
  mvprintw(9,48,players[1]->lastMove.c_str());

  // Player 2
  gameDisplay.drawBox(10, 11, 13, 3, 0);    // Money
  sprintf(tmpstr, "$%d", players[2]->wallet);
  mvprintw(12,11,tmpstr);
  gameDisplay.drawBox(10, 13, 13, 3, 0);    // Last action
  mvprintw(14,11,players[2]->lastMove.c_str());

  // Player 3
  gameDisplay.drawBox(10, 23, 13, 3, 0);    // Money
  sprintf(tmpstr, "$%d", players[3]->wallet);
  mvprintw(24,11,tmpstr);
  gameDisplay.drawBox(10, 25, 13, 3, 0);    // Last action
  mvprintw(26,11,players[3]->lastMove.c_str());

  // Player 4    HUMAN
  gameDisplay.drawBox(35, 33, 13, 3, 0);    // Money
  sprintf(tmpstr, "$%d", players[0]->wallet);
  mvprintw(34,36,tmpstr);
  gameDisplay.drawBox(35, 35, 13, 3, 0);    // Last action
  mvprintw(36,36,players[0]->lastMove.c_str());

  // Player 5
  gameDisplay.drawBox(78, 23, 13, 3, 0);    // Money
  sprintf(tmpstr, "$%d", players[4]->wallet);
  mvprintw(24,79,tmpstr);
  gameDisplay.drawBox(78, 25, 13, 3, 0);    // Last action
  mvprintw(26,79,players[4]->lastMove.c_str());

  // Player 6
  gameDisplay.drawBox(78, 11, 13, 3, 0);    // Money
  sprintf(tmpstr, "$%d", players[5]->wallet);
  mvprintw(12,79,tmpstr);
  gameDisplay.drawBox(78, 13, 13, 3, 0);    // Last action
  mvprintw(14,79,players[5]->lastMove.c_str());

}

void Dealer::dealRiver(){
  //cout << "Dealing the river." << endl;
  community.push_back(deck.dealCard());
  //cout << "Community cards: " << Deck::displayHand(community) << endl;
  mvprintw(15,51,"River");
  gameDisplay.displayCard(62,16,community.back().suit+1,community.back().value+2, A_BOLD);

}

void Dealer::dealTurn(){
  //cout << "Dealing the turn." << endl;
  community.push_back(deck.dealCard());
  mvprintw(15,51,"Turn");
  gameDisplay.displayCard(56,16,community.back().suit+1,community.back().value+2, A_BOLD);
  //cout << "Community cards: " << Deck::displayHand(community) << endl;
}

void Dealer::dealFlop(){
  //cout << "Dealing the flop." << endl;
  for(int i = 0; i < 3; i++){
    community.push_back(deck.dealCard());
  }
  // Flop
  mvprintw(15,51,"Flop");
  gameDisplay.displayCard(38,16,community[0].suit+1,community[0].value+2, A_BOLD);
  gameDisplay.displayCard(44,16,community[1].suit+1,community[1].value+2, A_BOLD);
  gameDisplay.displayCard(50,16,community[2].suit+1,community[2].value+2, A_BOLD);
  gameDisplay.displayCard(56,16,0,0, A_BOLD);
  gameDisplay.displayCard(62,16,0,0, A_BOLD);
  //gameDisplay.drawBox(46, 23, 15, 3, 0);		// Money in Side Pot
  //mvprintw(24,47,"Side Pot");
  //cout << "Community cards: " << Deck::displayHand(community) << endl;
}

// have the user enter the amount to raise
int User::getAmountForMove(Dealer* d){
  gameDisplay.drawBox(46, 21, 15, 3, 0);		// Money in Pot
  mvprintw(22,47,"Pot: $"+d->pot);
  for(;;){
    key2 = gameDisplay.captureInput();
    keynew = key2 - 48;

    if ((keynew >= 0) && (keynew <= 9)){
      bet = (bet * 10) + keynew;
      messageString.str("");
      messageString << "Press SPACE to confirm                           Money raising: " << bet;
      gameDisplay.bannerBottom(messageString.str());
    }

    if (keynew == -16){
      if (bet != 0){
        gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
        mvprintw(36,36,"Raise");								
        messageString.str("");
        messageString << "You bet " << bet << " chip(s)";
        gameDisplay.bannerBottom(messageString.str());
        return bet;
        bet = 0;
      }
    }
  }
}

// have the user enter their move, store it for later
Move User::getMove(Dealer* d){
  // display class will return button pressed
  // "raise", "call", "fold", "allin"

  char potstr[21];
  gameDisplay.drawBox(46, 21, 15, 3, 0);		// Money in Pot
  sprintf(potstr, "Pot: $%d", d->pot);
  mvprintw(22,47,potstr);

  d->updateValuesOnScreen();

  for (;;) {
    // Refresh every textbox
    // Money per player
    // Pot Money
    // Side Pot Money
    // CPU actions
    // using a stringstream rather than a string to make making the banner easier
    if (isTurn){
      // calls the game display to capture some input
      key = gameDisplay.captureInput();
      keynew = key - 48;
      // if a mouse event occurred
      if (key == -1) {
        // make a banner message
        messageString.str("");
        messageString << "A mouse event occurred x=" \
          << gameDisplay.getMouseEventX() << ", y=" \
          << gameDisplay.getMouseEventY() << ", bstate=" \
          << gameDisplay.getMouseEventButton();
        // display a banner message
        gameDisplay.bannerTop(messageString.str());
        // record the location of the mouse event
        cardX = gameDisplay.getMouseEventX();
        cardY = gameDisplay.getMouseEventY();
        // Some of the mouse click values are defined in display.h
        // check if it was a left click
        if (gameDisplay.getMouseEventButton()&LEFT_CLICK) {
          // Top Left
          // Check/Call
          if((cardX >= 50) && (cardX <= 68) && (cardY >= 28) && (cardY <= 33)){
            gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
            mvprintw(36,36,"Check/Call");
            messageString.str("");
            messageString << "You Checked/Called";
            gameDisplay.bannerBottom(messageString.str());
            return moveFromString("call");
          }

          // Bottom Left
          else if((cardX >= 50) && (cardX <= 68) && (cardY >= 35) && (cardY <= 40)){
            mvprintw(37,55,"Cheater   ");
            messageString.str("");
            messageString << "You Cheated";
            gameDisplay.bannerBottom(messageString.str());
          }
          // Top Middle
          // Raise
          else if((cardX >= 69) && (cardX <= 86) && (cardY >= 28) && (cardY <= 33)){
            messageString.str("");
            messageString << "Press SPACE to confirm                           Money raising: " << bet;
            gameDisplay.bannerBottom(messageString.str());
            return moveFromString("raise");
          }
          // Bottom Middle
          // ALL IN
          else if((cardX >= 69) && (cardX <= 86) && (cardY >= 35) && (cardY <= 40)){
            gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
            mvprintw(36,36,"ALL IN");
            messageString.str("");
            messageString << "You went ALL IN!";
            gameDisplay.bannerBottom(messageString.str());
            return moveFromString("allin");
          }
          // Top Right
          // Fold
          else if((cardX >= 87) && (cardX <= 105) && (cardY >= 28) && (cardY <= 33)){
            gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
            mvprintw(36,36,"Fold");
            messageString.str("");
            messageString << "You Folded";
            gameDisplay.bannerBottom(messageString.str());
            return moveFromString("fold");
          }
          // Bottom Right
          // Quit
          else if((cardX >= 87) && (cardX <= 105) && (cardY >= 35) && (cardY <= 40)){
            exit(0);
          }
        }
      } 
    }
  }
}
/*
 * This is the interrupt service routine called when the resize screen 
 * signal is captured.
 */
void detectResize(int sig) {
  // update the display class information with the new window size
  gameDisplay.handleResize(sig);
  // re-enable the interrupt for a window resize
  signal(SIGWINCH, detectResize);
  /*INSERT YOUR OWN SCREEN UPDATE CODE instead of stub_PrintResize*/
  stub_PrintResize();
}

/*
 * This is a simple stub that should be replaced with what the game does
 * when the screen resizes. 
 */
void stub_PrintResize(void) {
  // gets the new screen size
  int cols = gameDisplay.getCols();
  int lines = gameDisplay.getLines();
  // setups a message stream
  stringstream messageString;
  messageString << "Terminal is " << cols << "x" << lines;
  // prints out the information of the new screen size in a top banner
  gameDisplay.bannerTop(messageString.str());
}

