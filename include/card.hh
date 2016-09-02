#ifndef CARD_HH
#define CARD_HH
#include <stddef.h>

class Card
{
public:
    Card(const size_t& suit, const size_t& value):suit(suit), value(value){}

    size_t get_suit()const;
    size_t get_value()const;
    bool is_valid()const;
    bool operator<(const Card&)const;

private:
    const size_t suit;
    const size_t value;

    Card(const Card& card);
    Card& operator=(const Card&);
};

#endif // CARD_HH
