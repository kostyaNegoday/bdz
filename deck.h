#ifndef DECK_H
#define DECK_H
#include "card.h"

struct  deck{
    struct card *cards[CARD];
    short int count; // карт в колоде сейчас
    short int masscount; //вместимость колоды
};

int deckInit(struct deck *deck);
int deckStart (struct deck *deck, struct card *card);
int deckGivecard(struct deck *deck);
void decksort(struct deck *deck);

#endif


