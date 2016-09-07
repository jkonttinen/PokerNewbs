#ifndef DECK_HH
#define DECK_HH

#include "card.hh"
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>

class CardContainer
{
public:
    CardContainer(){}
    virtual ~CardContainer();

    void add_card(Card* card) {cards.push_back(card);}
    void add_card(Card* card,const size_t&);
    Card* remove_card();
    Card* remove_card(const Card& card);
    Card* remove_card(const size_t&);
    std::vector<Card*> get_cards() const {return cards;}

    const std::string suits = "CDHS";
    const std::string values = "23456789TJQKA";
protected:
    std::vector<Card*> cards;
private:
    CardContainer(const CardContainer&);
    CardContainer& operator=(const CardContainer&);
};

std::ostream& operator<<(std::ostream&, const CardContainer&);

class Deck : public CardContainer
{
public:
    Deck();
    void shuffle();
};

class TableCards : public CardContainer
{
public:
    TableCards(){}
};

class PocketCards : public CardContainer
{
public:
    PocketCards():wins(0),draws(0),losses(0){}
    void add_result(const size_t&);
    std::string get_results()const;
    std::string get_results_pct()const;
private:
    size_t wins;
    size_t draws;
    size_t losses;
};

class PokerHand : public CardContainer
{
public:
    PokerHand():CardContainer(){handRank = unranked;}
    PokerHand(const std::vector<Card*>&);

    enum rank {
        high,
        pair,
        two_pair,
        trips,
        straight,
        flush,
        full_house,
        quads,
        straight_flush,
        unranked = -1
    };

    const std::vector<std::string> hand = {"high card", "pair","two pair","trips","straight","flush","full_house","quads","straight flush"};

    enum rank get_rank()const{return handRank;}
    std::vector<size_t> get_secRank()const{return secRank;}

    bool operator<(const PokerHand&)const;
private:
    enum rank handRank;
    std::vector<size_t> secRank;
    void calculate_rank();

};
#endif // DECK_HH
