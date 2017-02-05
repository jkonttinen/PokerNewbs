#include "../include/card.hh"

bool Card::is_valid() const
{
    if (suit < 4 && value < 15 && value > 1) return true;
    else return false;
}

size_t Card::get_suit() const
{
    return suit;
}

size_t Card::get_value() const
{
    return value;
}

bool Card::operator<(const Card& card) const
{
    size_t card1 = this->value, card2 = card.get_value();
    if (card1 == card2) return this->suit < card.get_suit();
    return card1 < card2;
}
