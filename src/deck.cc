#include "../include/deck.hh"

CardContainer::~CardContainer()
{
    for (auto it = cards.begin(); it != cards.end(); it++)
        delete *it;
    cards.clear();
}

void CardContainer::add_card(Card* card, const size_t& i)
{
    cards.insert(cards.begin()+i, card);
}

Card* CardContainer::remove_card()
{
    Card* card = cards[0];
    cards.erase(cards.begin());

    return card;
}

Card* CardContainer::remove_card(const Card& card)
{
    for (auto it = cards.begin();it != cards.end();it++)
        if ((*it)->get_suit() == card.get_suit() && (*it)->get_value() == card.get_value())
        {
            Card* c = *it;
            cards.erase(it);
            return c;
        }
    return NULL;
}

Card* CardContainer::remove_card(const size_t& i)
{
    Card* c = cards[i];
    cards.erase(cards.begin()+i);
    return c;
}

std::ostream& operator<< (std::ostream& os, const CardContainer& cards)
{
    auto c = cards.get_cards();
    for (size_t i = 0; i < c.size(); i++)
    {
        os << cards.values[c[i]->get_value()-2] << cards.suits[c[i]->get_suit()] <<" ";
    }

    return os;
}

Deck::Deck()
{
    for (size_t i = 0; i < 52; i++)
        add_card(new Card(i/13, i%13+2));
//    shuffle();
}

void Deck::shuffle()
{
    std::srand ( unsigned ( std::time(0) ) );

    for (size_t i = 0; i < 100; i++)
        std::random_shuffle(cards.begin(), cards.end());
}

void PocketCards::add_result(const size_t& num)
{
    if (num == 2) wins++;
    else if (num == 1) draws++;
    else losses++;
}

std::string PocketCards::get_results()const
{
    std::stringstream str;
    str << "Wins: " << wins << std::endl;
    str << "Losses: " << losses << std::endl;
    str << "Ties: " << draws << std::endl;

    return str.str();
}

std::string PocketCards::get_results_pct()const
{
    std::stringstream str;
    size_t sum = wins+losses+draws;
    str << "Equity: " <<  100*((1.0 * wins) / sum + 0.5*(1.0*draws / sum)) << std::endl;

    return str.str();
}

PokerHand::PokerHand(const std::vector<Card*>& hand)
{
    for (size_t i = 0; i < 5; i++)
        cards.push_back(new Card(hand[i]->get_suit(),hand[i]->get_value()));

    std::sort(cards.begin(),cards.end(),[](Card* c1,Card* c2)
    {
        return *c1 < *c2;
    });

    calculate_rank();
}

void PokerHand::calculate_rank()
{
    bool straight = true, flush = true, last = false;
    size_t pair[2] = {0,0};

    for (size_t i = 0; i < 4; i++)
    {
        if (straight == true && i == 3 &&
                cards[i]->get_value() == 5 && cards[i+1]->get_value() == 14) secRank.push_back(5);
        else if (cards[i]->get_value() + 1 != cards[i+1]->get_value()) straight = false;

        if (cards[i]->get_suit() != cards[i+1]->get_suit()) flush = false;

        if (cards[i]->get_value() == cards[i+1]->get_value())
        {
            if (!pair[last]) secRank.push_back(cards[i]->get_value());
            pair[last]++;
        }
        else if (pair[last]) last = true;
    }

    if (straight)
    {
        handRank = rank::straight;
        if (flush) handRank = rank::straight_flush;
        if (!secRank.size()) secRank.push_back(cards[4]->get_value());
    }
    else if (flush) handRank = rank::flush;
    else if (pair[0] == 3) handRank = rank::quads;
    else if (pair[0] + pair[1] == 3)
    {
        handRank = rank::full_house;
        if (pair[0] == 2) std::reverse(secRank.begin(),secRank.end());
    }
    else if (pair[0] == 2) handRank = rank::trips;
    else if (pair[0] + pair[1] == 2)
    {
        handRank = rank::two_pair;
        std::sort(secRank.begin(),secRank.end());
    }
    else if (pair[0]) handRank = rank::pair;
    else handRank = rank::high;
}

bool PokerHand::operator<(const PokerHand& hand)const
{
    if (handRank != hand.get_rank())
        return (handRank < hand.get_rank());
    else if (secRank.size())
        for (size_t i = secRank.size(); i > 0 ; i--)
            if (secRank[i-1] != hand.get_secRank()[i-1])
                return (secRank[i-1] < hand.get_secRank()[i-1]);

    size_t i = 4;
    std::vector<Card*> help = hand.get_cards();
    while(!(*cards[i] < *help[i]) && !(*help[i] < *cards[i]))
    {
        i--;
        if (i == 0) break;
    }
    return (*(cards[i]) < *(help[i]));
}
