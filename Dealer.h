class Dealer {
  public:
    Deck deck;
    Card[] community;
    int pot;
    Player[] players;
    Player *currentPlayer;
    Player *smallBlindHolder;
    Player[] determineWinner();
    void dealHands();
    void dealFlop();
    void dealRiver();
    void dealTurn();
    void kick(Player playerToKick);
    void startGame();
    void endGame();
    void restartGame();
    bool userStillAlive();
}
