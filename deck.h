#ifndef DECK_H
#define DECK_H
#include "card.h"

struct  deck{
    struct card *cards;
    short int count; // карт в колоде сейчас
    short int masscount; //вместимость колоды
};

int deckInit(struct deck *deck);
int deckGivecard(struct deck *deck, struct card *outcard);
void deckSort(struct deck *deck);
int deckDestr(struct deck *deck);


#endif


