enum Suit {SPADES, DIAMONDS, HEARTS, CLUBS}
enum Value {ONE, TWO,
      THREE, FOUR,
      FIVE, SIX,
      SEVEN, EIGHT,
      NINE, TEN,
      JACK, QUEEN,
      KING, ACE}

class Card {
  public:
    Card(Suit, Value);
    ~Card(void);
    Suit suit;
    Value value;
}
