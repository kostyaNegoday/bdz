#ifndef HAND_H
#define HAND_H
#include "card.h"

typedef struct {
    CardNode *head;
    int count;
} hand;

void handinit(hand *hand);
int handsorted(hand *hand, CardNode *node);
int handscore(hand *hand);
CardNode *handtakeall(hand *hand);
void handclear(hand *hand);

#endif