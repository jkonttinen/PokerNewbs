#include <iostream>
#include "include/card.hh"
#include "include/deck.hh"
#include "gamesituation.hh"

int main()
{


    Deck* deck = new Deck();

    deck->shuffle();

//    PocketCards* pc1 = new PocketCards();
    TableCards* tc = new TableCards();


    std::vector<PocketCards*> pcVect;
    for (size_t i = 0;i < 4;i++)
    {
        PocketCards* pc = new PocketCards();
        for (size_t j = 0;j < 2;j++)
            pc->add_card(deck->remove_card());
        pcVect.push_back(pc);
    }
//    for (size_t i = 0;i < 3;i++)
//        tc->add_card(deck->remove_card());

    GameSituation gs(deck,tc,pcVect);

//    std::cout << *deck << std::endl<< std::endl;
    std::cout << *tc << std::endl<< std::endl;
    gs.preflop(0);

    for (size_t i = 0;i < pcVect.size();i++)
    {
        std::cout << *pcVect[i] << std::endl<<std::endl;
        std::cout << pcVect[i]->get_results() << std::endl<<std::endl;
    }

    return 0;
}
