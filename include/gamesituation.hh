#ifndef GAMESITUATION_HH
#define GAMESITUATION_HH

#include "card.hh"
#include "deck.hh"
#include <iostream>

class GameSituation
{
public:
    GameSituation(Deck* deck, TableCards* tc, std::vector<PocketCards*> pc):deck(deck),tableCards(tc),pocketCards(pc) {}
    virtual ~GameSituation();

    void compare_hands(const std::vector<PokerHand*>&);

    PokerHand* on_the_river(const size_t &);
    void on_the_turn(const size_t &);
    void on_the_flop(const size_t &);
    void preflop(const size_t &);

private:
    Deck* deck;
    TableCards* tableCards;
    std::vector<PocketCards*> pocketCards;
};

#endif // GAMESITUATION_HH
