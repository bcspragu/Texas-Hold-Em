#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class Dealer {
  public:
    Dealer();
    ~Dealer(void);
    Deck deck;
    vector<Card> community;
    int pot;
    vector<Player> players;
    Player *currentPlayer;
    Player *smallBlindHolder;
    Player* determineWinner();
    void dealHands();
    void dealFlop();
    void dealRiver();
    void dealTurn();
    void kick(Player playerToKick);
    void startGame();
    void endGame();
    void restartGame();
    bool userStillAlive();
};

#endif
