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
    std::vector<Card> community;
    int pot;
    std::vector<Player> players;
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
    static bool royalFlush(std::vector<Card> hand);
    static bool straightFlush(std::vector<Card> hand);
    static bool fourOfAKind(std::vector<Card> hand);
    static Value valueOfFourOfAKind(std::vector<Card> hand);
    static bool fullHouse(std::vector<Card> hand);
    static bool flush(std::vector<Card> hand);
    static bool straight(std::vector<Card> hand);
    static bool threeOfAKind(std::vector<Card> hand);
    static Value valueOfThreeOfAKind(std::vector<Card> hand);
    static bool twoPair(std::vector<Card> hand);
    static Value higherPair(std::vector<Card> hand);
    static Value lowerPair(std::vector<Card> hand);
    static bool pair(std::vector<Card> hand);
    static Value valueOfPair(std::vector<Card> hand);
    static Value highestValue(std::vector<Card> hand);
    static int scoreHand(std::vector<Card> hand);
};

#endif
