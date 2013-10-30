#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include "SuitValue.h"
#include "Deck.h"

class Player;
class User;
class Card;
class Computer;

const int smallBlind = 25;
const int largeBlind = 50;

class Dealer {
  public:
    Dealer();
    Deck deck;
    std::vector<Card> community;
    int pot;
    int betValue;
    int smallBlindLoc;
    int numPlayers;
    std::vector<Player*> determineWinner();
    std::vector<Player*> players;
    std::vector<Player*> currentRound;
    void dealHands();
    void dealFlop();
    void dealRiver();
    void dealTurn();
    void kick(Player playerToKick);
    void startGame();
    void endGame();
    void restartGame();
    bool userStillAlive(User user);
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
    int scoreBestHand(std::vector<Card> hand);
    std::vector<Card> bestHand(std::vector<Card> hand);
    Player* nextPlayer(std::vector<Computer> computers, User* user);
  private:
    std::vector<Card> fiveCardHand(std::vector<Card> sevenCardHand, int index1, int index2);
    void roundOfBetting(int offset);
    int playersStillIn(std::vector<Player*> current);
};

#endif
