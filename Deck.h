#include <vector>
#include "Card.h"

using namespace std;

class Deck {
  public:
    Deck();
    ~Deck(void);
    vector<Card> cards;
    void shuffle();
}
