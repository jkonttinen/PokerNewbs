#include <iostream>
#include <fstream>
#include "card.hh"
#include "deck.hh"
#include "gamesituation.hh"

int main()
{
    std::fstream file;

    Deck* deck = new Deck();

    //deck->shuffle();

    TableCards* tc = new TableCards();

    std::cout << *deck << std::endl;
    std::vector<PokerHand*> phVect;

    for (size_t i0 = 0; i0 < deck->get_cards().size() - 4; i0++)
    {
        tc->add_card(deck->remove_card(i0));
        for (size_t i1 = i0; i1 < deck->get_cards().size() - 3; i1++)
        {
            tc->add_card(deck->remove_card(i1));
            for (size_t i2 = i1; i2 < deck->get_cards().size() - 2; i2++)
            {
                tc->add_card(deck->remove_card(i2));
                for (size_t i3 = i2; i3 < deck->get_cards().size() - 1; i3++)
                {
                    tc->add_card(deck->remove_card(i3));
                    for (size_t i4 = i3; i4 < deck->get_cards().size(); i4++)
                    {
                        tc->add_card(deck->remove_card(i4));
                        PokerHand* ph = new PokerHand(tc->get_cards());
                        phVect.push_back(ph);

                        deck->add_card(tc->remove_card(4),i4);
                    }
                    deck->add_card(tc->remove_card(3),i3);
                }
                deck->add_card(tc->remove_card(2),i2);
            }
            deck->add_card(tc->remove_card(1),i1);
        }
        deck->add_card(tc->remove_card(0),i0);
        std::cout << i0 << std::endl;
    }
    std::sort(phVect.begin(),phVect.end(),[](PokerHand* ph1,PokerHand* ph2)
    {
        return *ph1 < *ph2;
    });

    file.open("handrank.txt", std::fstream::out);
    size_t value = 0;
    for (size_t i = 0;i < phVect.size();i++)
    {
        if (i != 0 && *phVect[i-1] <*phVect[i]) value++;
        file << value << " " << *phVect[i] << std::endl;
    }

    for (auto it = phVect.begin();it != phVect.end();it++)
        delete *it;
    phVect.clear();
//    PocketCards* pc1 = new PocketCards();

//    std::vector<PocketCards*> pcVect;
//    for (size_t i = 0;i < 6;i++)
//    {
//        PocketCards* pc = new PocketCards();
//        for (size_t j = 0;j < 5;j++)
//            pc->add_card(deck->remove_card());
//        pcVect.push_back(pc);
//    }
//    for (size_t i = 0;i < 4;i++)
//        tc->add_card(deck->remove_card());

//    PocketCards* pc = new PocketCards();
//    PocketCards* pc1 = new PocketCards();
//    pc->add_card(deck->remove_card(Card(0,5)));
//    pc->add_card(deck->remove_card(Card(0,6)));
//    pcVect.push_back(pc);
//
//    for (size_t i = 0;i < deck->get_cards().size()-1;i++)
//    {
//        for (size_t j = i+1;j < deck->get_cards().size();j++)
//        {
//            pc1->add_card(deck->remove_card(j));
//            pc1->add_card(deck->remove_card(i));
//            pcVect.push_back(pc1);
//            GameSituation gs(deck,tc,pcVect);
//
//            gs.preflop(0);
//            std::cout << *pc << std::endl;
//            std::cout << *pc1 << std::endl;
//            std::cout << pcVect[0]->get_results_pct() << std::endl << std::endl;
//            file << pcVect[0]->get_results_pct() << std::endl;
//            deck->add_card(pc1->remove_card(1),i);
//            deck->add_card(pc1->remove_card(),j);
//
//            pcVect.pop_back();
//        }
//    }

//    std::cout << *deck << std::endl<< std::endl;
//    gs.preflop(0);
//    std::cout << *tc << std::endl<< std::endl;
//    for (size_t i = 0;i < pcVect.size();i++)
//    {
//        std::cout << *pcVect[i] << std::endl<<std::endl;
//        std::cout << pcVect[i]->get_results() << std::endl<<std::endl;
//        std::cout << pcVect[i]->get_results_pct() << std::endl << std::endl;
//    }
//    delete pc;
//    delete pc1;
    delete tc;
    delete deck;
//    pcVect.clear();

    return 0;
}
