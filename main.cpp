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
#include "Computer.h"
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

char key;
char key2;
int cardX = 0;
int cardY = 0;
void setText(string target, string text);
/*
 * This is the main function that starts the driver artifact.
 * This function demonstrates some of the abilities of the Display class
 */
int main(int argc, char* argv[])
{
  signal(SIGWINCH, detectResize); // enable the window resize signal
  // Player 1
  gameDisplay.drawBox(47, 6, 13, 3, 0);		// Money
  gameDisplay.drawBox(47, 8, 13, 3, 0);		// Last action
  gameDisplay.displayCard(47,2,0,0, A_BOLD);
  gameDisplay.displayCard(54,2,0,0, A_BOLD);

  // Player 2
  gameDisplay.drawBox(10, 11, 13, 3, 0);		// Money
  gameDisplay.drawBox(10, 13, 13, 3, 0);		// Last action
  gameDisplay.displayCard(10,7,0,0, A_BOLD);
  gameDisplay.displayCard(17,7,0,0, A_BOLD);

  // Player 3
  gameDisplay.drawBox(10, 23, 13, 3, 0);		// Money
  gameDisplay.drawBox(10, 25, 13, 3, 0);		// Last action
  gameDisplay.displayCard(10,19,0,0, A_BOLD);
  gameDisplay.displayCard(17,19,0,0, A_BOLD);

  // Player 4    HUMAN
  gameDisplay.drawBox(35, 33, 13, 3, 0);		// Money
  gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
  gameDisplay.displayCard(35,29,0,0, A_BOLD);
  gameDisplay.displayCard(42,29,0,0, A_BOLD);

  // Player 5
  gameDisplay.drawBox(78, 23, 13, 3, 0);		// Money
  gameDisplay.drawBox(78, 25, 13, 3, 0);		// Last action
  gameDisplay.displayCard(78,19,0,0, A_BOLD);
  gameDisplay.displayCard(85,19,0,0, A_BOLD);

  // Player 6
  gameDisplay.drawBox(78, 11, 13, 3, 0);		// Money
  gameDisplay.drawBox(78, 13, 13, 3, 0);		// Last action
  gameDisplay.displayCard(78,7,0,0, A_BOLD);
  gameDisplay.displayCard(85,7,0,0, A_BOLD);

  // Choices
  mvprintw(34,74,"Options");

  gameDisplay.drawBox(50, 28, 19, 6, 0);		// Top Left
  setText("B11","Check/Call");
  gameDisplay.drawBox(50, 35, 19, 6, 0);		// Bottom Left
  setText("B12","Start Game");
  gameDisplay.drawBox(69, 28, 18, 6, 0);		// Top Middle
  setText("B21","Raise");
  gameDisplay.drawBox(69, 35, 18, 6, 0);		// Bottom Middle
  setText("B22","ALL IN");
  gameDisplay.drawBox(87, 28, 19, 6, 0);		// Top Right
  setText("B31","Fold");
  gameDisplay.drawBox(87, 35, 19, 6, 0);		// Bottom Right
  setText("B32","Quit");

  //Draw blank community cards
  gameDisplay.displayCard(38,16,0,0, A_BOLD);
  gameDisplay.displayCard(44,16,0,0, A_BOLD);
  gameDisplay.displayCard(50,16,0,0, A_BOLD);
  gameDisplay.displayCard(56,16,0,0, A_BOLD);
  gameDisplay.displayCard(62,16,0,0, A_BOLD);
  bool onGoing = true;
  while(onGoing){
    key = gameDisplay.captureInput();
    keynew = key - 48;
    // if a mouse event occurred
    if (key == -1) {
      // record the location of the mouse event
      cardX = gameDisplay.getMouseEventX();
      cardY = gameDisplay.getMouseEventY();
      if((cardX >= 50) && (cardX <= 68) && (cardY >= 35) && (cardY <= 40)){
        setText("B12","Game on");
        messageString.str("");
        messageString << "Playing";
        gameDisplay.bannerBottom(messageString.str());
        Dealer d;
        onGoing = false;
      }
    }
  }
  return 0;

}

Dealer::Dealer(){
  pot = 0;
  numPlayers = 6;
  User* user = new User(500);
  user->ID = 1;
  players.push_back(user);
  for(int i = 1; i < numPlayers; i++){
    players.push_back(new Computer(500));
    players.back()->ID = i+1;
  }

  std::vector<Player*>::iterator pitr;

  smallBlindLoc = -1;
  //Game loop

  while((*players.front()).wallet > largeBlind){

    //Fill and shuffle the deck before each hand
    deck.fill();
    deck.shuffle();

    //Clear out the community cards
    community.clear();

    //Kill all the players that can't make large blind
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      if((**pitr).wallet < largeBlind){
        //cout << "Player " << (**pitr).ID << " has ran out of money" << endl;
        (*pitr) = NULL; //GET NULLIFIED
        numPlayers--;
      }
    }

    if(numPlayers == 1){
      //Game Over, you win
    }

    dealHands();
    //Resetting things between rounds

    betValue = largeBlind;
    pot = 0;

    do{
      smallBlindLoc = (smallBlindLoc + 1) % players.size();
    }
    while(players[smallBlindLoc] == NULL);
    currentRound = players;
    players[smallBlindLoc]->wallet -= smallBlind;
    //cout << "Player " << players[smallBlindLoc]->ID << " has small blind" << endl;
    players[(smallBlindLoc+1) % players.size()]->wallet -= largeBlind;
    //cout << "Player " << players[(smallBlindLoc+1) % players.size()]->ID << " has large blind" << endl;
    pot += smallBlind+largeBlind;


    roundOfBetting(2);
    dealFlop();
    roundOfBetting(0);
    dealTurn();
    roundOfBetting(0);
    dealRiver();
    roundOfBetting(0);
    showAllCards();

    std::vector<Player*> winners = determineWinner();
    stringstream win_strm;
    string win_str = "";
    for(pitr = winners.begin(); pitr != winners.end(); ++pitr){
      if((*pitr) != NULL){
        (**pitr).wallet += pot/winners.size();
        win_strm << "Player " << (**pitr).ID << ",";
        win_str = win_strm.str();
        win_str = win_str.substr(0,win_str.length()-1);
        win_str += " won.";
        mvprintw(15,51,win_str.c_str());

      }
    }

  }
  if((*players.front()).wallet < largeBlind){
    //cout << "User has lost the game." << endl;
  }
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
  setText("C","River");
  gameDisplay.displayCard(62,16,community.back().suit+1,community.back().value+2, A_BOLD);

}

void Dealer::dealTurn(){
  //cout << "Dealing the turn." << endl;
  community.push_back(deck.dealCard());
  setText("C","Turn");
  gameDisplay.displayCard(56,16,community.back().suit+1,community.back().value+2, A_BOLD);
  //cout << "Community cards: " << Deck::displayHand(community) << endl;
}

void Dealer::dealFlop(){
  //cout << "Dealing the flop." << endl;
  for(int i = 0; i < 3; i++){
    community.push_back(deck.dealCard());
  }
  // Flop
  setText("C","Flop");
  gameDisplay.displayCard(38,16,community[0].suit+1,community[0].value+2, A_BOLD);
  gameDisplay.displayCard(44,16,community[1].suit+1,community[1].value+2, A_BOLD);
  gameDisplay.displayCard(50,16,community[2].suit+1,community[2].value+2, A_BOLD);
  gameDisplay.displayCard(56,16,0,0, A_BOLD);
  gameDisplay.displayCard(62,16,0,0, A_BOLD);
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
      messageString << "Press SPACE to confirm                Money raising: " << bet;
      gameDisplay.bannerBottom(messageString.str());
    }

    if (keynew == -16){
      if (bet != 0){
        gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
        mvprintw(36,36,"Raise");								
        messageString.str("");
        messageString << "You bet " << bet << " chip(s)";
        gameDisplay.bannerBottom(messageString.str());
        int temp = bet;
        bet = 0;
        return temp;
      }
    }
  }
}

Move Computer::getMove(Dealer* d){
  int handValue;
  int decision;

  std::vector<Card> allCards;
  allCards.insert(allCards.end(), hand.begin(), hand.end());
  allCards.insert(allCards.end(), (*d).community.begin(),(*d).community.end());

  //if only pocket cards use ratePocketCards method for decision
  if(allCards.size() <= 2){    
    handValue = ratePocketCards(allCards);
  }else if(allCards.size() == 5){
    handValue = Dealer::scoreHand(allCards);
  }else if ((allCards.size()) >= 6){
    handValue = (*d).scoreBestHand(hand);
  }
  decision = getDecision(handValue);

  if((decision == 0) || (decision == 3)){
    raiseAmount = 0;
    //move = 0;
    lastMove = "Call";
    return CALL;
  }else if ((decision == 1) || (decision == 4)){
    lastMove = "Raise";
    raiseAmount = getRaiseAmount(d);
    return RAISE;
  }else if ((decision == 2) || (decision == 5)){
    //move = 2;
    alreadyFolded = true;
    lastMove = "Fold";
    return FOLD;
  }
  return CALL;
}

int Computer::getAmountForMove(Dealer* d){
  return raiseAmount;
}

int Computer::ratePocketCards(std::vector<Card> pocket){

  int pocketValue;
  std::sort(pocket.begin(),pocket.end());


  Card lowCard = pocket.front();
  Card highCard = pocket.back();

  std::map<Value, double> cardPoints; 

  cardPoints[ACE]=10;
  cardPoints[KING]=8;
  cardPoints[QUEEN]=7;
  cardPoints[JACK]=6;
  cardPoints[TEN]=5;
  cardPoints[NINE]=4.5;
  cardPoints[EIGHT]=4;
  cardPoints[SEVEN]=3.5;
  cardPoints[SIX]=3;
  cardPoints[FIVE]=2.5;
  cardPoints[FOUR]=2;
  cardPoints[THREE]=1.5;
  cardPoints[TWO]=1;

  pocketValue = cardPoints[highCard.value];

  if((highCard.value)==(lowCard.value)){
    if((highCard.value)<=2){
      pocketValue=5;
    }else{
      pocketValue = pocketValue*2;
    }
  }
  if((highCard.suit) == (lowCard.suit)){
    pocketValue = pocketValue + 2;
  }
  if(((highCard.value) == (lowCard.value)+1) || ((highCard.value) == ((lowCard.value)-1))){
    pocketValue = pocketValue + 1;
  }
  if(((highCard.value) == (lowCard.value)+2) || ((highCard.value) == ((lowCard.value)-2))){
    pocketValue = pocketValue - 1;
  }
  if(((highCard.value) == (lowCard.value)+3) || ((highCard.value) == ((lowCard.value)-3))){
    pocketValue = pocketValue - 2;
  }
  if(((highCard.value) == (lowCard.value)+4) || ((highCard.value) == ((lowCard.value)-4))){
    pocketValue = pocketValue - 4;
  }
  if(((highCard.value) == (lowCard.value)+5) || ((highCard.value) == ((lowCard.value)-5))){
    pocketValue = pocketValue - 5;
  }


  //cout<<highCard.value<<endl;
  //cout<< "Pocket Rateeee: " << pocketValue << endl;
  return pocketValue;

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
          lastMove = "Check";
          gameDisplay.bannerBottom(messageString.str());
          return CALL;
        }

        // Top Middle
        // Raise
        else if((cardX >= 69) && (cardX <= 86) && (cardY >= 28) && (cardY <= 33)){
          messageString.str("");
          messageString << "Press SPACE to confirm                           Money raising: " << bet;
          gameDisplay.bannerBottom(messageString.str());
          lastMove = "Raise";
          return RAISE;
        }
        // Bottom Middle
        // ALL IN
        else if((cardX >= 69) && (cardX <= 86) && (cardY >= 35) && (cardY <= 40)){
          gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
          mvprintw(36,36,"ALL IN");
          messageString.str("");
          messageString << "You went ALL IN!";
          gameDisplay.bannerBottom(messageString.str());
          lastMove = "Raise";
          return ALLIN;
        }
        // Top Right
        // Fold
        else if((cardX >= 87) && (cardX <= 105) && (cardY >= 28) && (cardY <= 33)){
          gameDisplay.drawBox(35, 35, 13, 3, 0);		// Last action
          mvprintw(36,36,"Fold");
          messageString.str("");
          messageString << "You Folded";
          gameDisplay.bannerBottom(messageString.str());
          lastMove = "Fold";
          return FOLD;
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

void Dealer::showAllCards(){
  std::vector<Player*>::iterator pitr;
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    int suit1 = (**pitr).hand.front().suit+1;
    int value1 = (**pitr).hand.front().value+2;
    int suit2 = (**pitr).hand.front().suit+1;
    int value2 = (**pitr).hand.front().value+2;
    int ypos,xpos;
    switch((**pitr).ID){
      case 1:
        xpos = 35;
        ypos = 29;
        break;
      case 2:
        xpos = 47;
        ypos = 2;
        break;
      case 3:
        xpos = 10;
        ypos = 19;
        break;
      case 4:
        xpos = 10;
        ypos = 7;
        break;
      case 5:
        xpos = 78;
        ypos = 19;
      case 6:
        xpos = 78;
        ypos = 7;
    }
    gameDisplay.displayCard(xpos,ypos,suit1,value1, A_BOLD);
    gameDisplay.displayCard(xpos+7,ypos,suit2,value2, A_BOLD);
  }
}

void Player::updateWallet(){
  const char* move = lastMove.c_str();
  char money[10];
  sprintf(money,"Wallet: $%d",wallet);
  switch(ID){
    case 1:
      setText("P1T",money);
      setText("P1B",move);
      break;
    case 2:
      setText("P2T",money);
      setText("P2B",move);
      break;
    case 3:
      setText("P3T",money);
      setText("P3B",move);
      break;
    case 4:
      setText("P4T",money);
      setText("P4B",move);
      break;
    case 5:
      setText("P5T",money);
      setText("P5B",move);
      break;
    case 6:
      setText("P6T",money);
      setText("P6B",move);
      break;
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

void setText(string target, string text){
  int xpos,ypos;
  if(target == "B11"){ //Box 1,1 top left
    ypos = 30;
    xpos = 55;
  }else if(target == "B12"){ //Box 1,2 bottom left
    ypos = 37;
    xpos = 55;
  }else if(target == "B21"){ //Box 2,1 top center
    ypos = 30;
    xpos = 75;
  }else if(target == "B22"){ //Box 1,2 bottom center
    ypos = 37;
    xpos = 75;
  }else if(target == "B31"){ //Box 3,1 top right
    ypos = 30;
    xpos = 94;
  }else if(target == "B32"){ //Box 3,2 bottom right
    ypos = 37;
    xpos = 94;
  }else if(target == "P1T"){ //Player 1 top box
    ypos = 34;
    xpos = 36;
  }else if(target == "P1B"){ //Player 1 bottom box
    ypos = 36;
    xpos = 36;
  }else if(target == "P2T"){ //Player 2 top box
    ypos = 7;
    xpos = 48;
  }else if(target == "P2B"){ //Player 2 bottom box
    ypos = 9;
    xpos = 48;
  }else if(target == "P3T"){ //Player 3 top box
    ypos = 24;
    xpos = 11;
  }else if(target == "P3B"){ //Player 3 bottom box
    ypos = 26;
    xpos = 11;
  }else if(target == "P4T"){ //Player 4 top box
    ypos = 12;
    xpos = 11;
  }else if(target == "P4B"){ //Player 4 bottom box
    ypos = 14;
    xpos = 11;
  }else if(target == "P5T"){ //Player 5 top box
    ypos = 24;
    xpos = 79;
  }else if(target == "P5B"){ //Player 5 bottom box
    ypos = 26;
    xpos = 79;
  }else if(target == "P6T"){ //Player 6 top box
    ypos = 12;
    xpos = 79;
  }else if(target == "P6B"){ //Player 6 bottom box
    ypos = 14;
    xpos = 79;
  }else if(target == "C"){ //Community header
    ypos = 15;
    xpos = 51;
  }
  mvprintw(ypos,xpos,"       ");
  mvprintw(ypos,xpos,text.c_str());
}
