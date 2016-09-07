#include "gamesituation.hh"

GameSituation::~GameSituation()
{
//    delete deck;
//    delete tableCards;
//    for (auto it = pocketCards.begin(); it != pocketCards.end(); it++)
//        delete *it;
//    pocketCards.clear();
}

std::vector<size_t> GameSituation::compare_hands(const std::vector<PokerHand*>& phVect, const std::vector<size_t>& spot,const size_t& round)
{

    std::vector<size_t> help = spot;

    PokerHand* ph1 = phVect[help[0]];
    PokerHand* ph2 = phVect[phVect.size()-round];

    if (!(*ph1 < *ph2) && !(*ph2 < *ph1))
        help.push_back(phVect.size()-round);
    else if (*ph1 < *ph2)
    {
        help.clear();
        help.push_back(phVect.size()-round);
    }

    if (round < phVect.size()-1)
        help = compare_hands(phVect,help,round+1);

    if (round == 1)
    {
        for (size_t i = 0;i < phVect.size();i++)
        {
            bool test = false;
            for (size_t j = 0;j < help.size();j++)
                if (help[j] == i) test = true;

            if (help.size() > 1 && test == true)
                pocketCards[i]->add_result(1);
            else if (test == true)
                pocketCards[i]->add_result(2);
            else pocketCards[i]->add_result(0);
        }
    }
    return help;
}

PokerHand* GameSituation::on_the_river(const size_t& num)
{
    PokerHand* best = new PokerHand();
    if (tableCards->get_cards().size() == 5)
    {

        if (pocketCards[num]->get_cards().size() == 2)
        {
            std::vector<Card*> cards = pocketCards[num]->get_cards();
            std::vector<Card*> tc = tableCards->get_cards();
            cards.insert(cards.end(),tc.begin(),tc.end());

            for (size_t i0 = 0; i0 < 3; i0++)
            {
                std::vector<Card*> hand;
                hand.push_back(cards[i0]);
                for (size_t i1 = i0+1; i1 < 4; i1++)
                {
                    hand.push_back(cards[i1]);
                    for (size_t i2 = i1+1; i2 < 5; i2++)
                    {
                        hand.push_back(cards[i2]);
                        for (size_t i3 = i2+1; i3 < 6; i3++)
                        {
                            hand.push_back(cards[i3]);
                            for (size_t i4 = i3+1; i4 < 7; i4++)
                            {
                                hand.push_back(cards[i4]);
                                PokerHand currentHand(hand);
                                if (*best < currentHand)
                                {
                                    delete best;
                                    best = new PokerHand(hand);
                                }
                                hand.pop_back();
                            }
                            hand.pop_back();
                        }
                        hand.pop_back();
                    }
                    hand.pop_back();
                }
                hand.pop_back();
            }
        }
        else if (pocketCards[num]->get_cards().size() >= 4)
        {
            std::vector<Card*> pc = pocketCards[num]->get_cards();
            std::vector<Card*> tc = tableCards->get_cards();

            for (size_t i0 = 0; i0 < pc.size()-1; i0++)
            {
                std::vector<Card*> hand;
                hand.push_back(pc[i0]);
                for (size_t i1 = i0+1; i1 < pc.size(); i1++)
                {
                    hand.push_back(pc[i1]);
                    for (size_t i2 = 0; i2 < tc.size()-2; i2++)
                    {
                        hand.push_back(tc[i2]);
                        for (size_t i3 = i2+1; i3 < tc.size()-1; i3++)
                        {
                            hand.push_back(tc[i3]);
                            for (size_t i4 = i3+1; i4 < tc.size(); i4++)
                            {
                                hand.push_back(tc[i4]);
                                PokerHand currentHand(hand);
                                if (*best < currentHand)
                                {
                                    delete best;
                                    best = new PokerHand(hand);
                                }
                                hand.pop_back();
                            }
                            hand.pop_back();
                        }
                        hand.pop_back();
                    }
                    hand.pop_back();
                }
                hand.pop_back();
            }
        }
    }
    return best;
}

void GameSituation::on_the_turn(const size_t& start)
{
    if (tableCards->get_cards().size() == 4)
        for (size_t i = start; i < deck->get_cards().size(); i++)
        {
            tableCards->add_card(deck->remove_card(i));
            std::vector<PokerHand*> phVect;

            for (size_t j = 0; j < pocketCards.size(); j++)
                phVect.push_back(on_the_river(j));

            compare_hands(phVect,std::vector<size_t>(1,0),1);
            deck->add_card(tableCards->remove_card(4),i);
            for (auto it = phVect.begin(); it != phVect.end(); it++)
                delete *it;
            phVect.clear();
        }
}

void GameSituation::on_the_flop(const size_t& start)
{
    if (tableCards->get_cards().size() == 3)
        for (size_t i = start; i < deck->get_cards().size()-1; i++)
        {
            tableCards->add_card(deck->remove_card(i));
            on_the_turn(i);
            deck->add_card(tableCards->remove_card(3),i);
        }
}

void GameSituation::preflop(const size_t& start)
{
    size_t round = tableCards->get_cards().size();
    for (size_t i = start; i < deck->get_cards().size()-(4-round); i++)
    {
        tableCards->add_card(deck->remove_card(i));
        if (round < 2) preflop(i);
        else on_the_flop(i);
        deck->add_card(tableCards->remove_card(round),i);
//        std::cout << i << " " << round << std::endl;
    }
}
