#ifndef DECK_H
#define DECK_H
#include "card.h"

typedef struct {
    CardNode *top;
    CardNode *bottom;
    int count;
} deck;

int deckinit(deck *deck);
CardNode *deckdraw(deck *deck);
void deckbottom(deck *deck, CardNode *chain);
int deckshuffle(deck *deck);
void deckdestroy(deck *deck);

#endif


