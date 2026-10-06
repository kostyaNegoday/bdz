#ifndef HAND_H
#define HAND_H
#include "card.h"
#include "deck.h"

struct hand {
    struct card *cards;
    short int count; // карт в руке сейчас
    short int masscount; //вместимость руки
};

int handInit(struct hand *hand);
int handGivecard(struct hand *hand, struct card *outcard);
int handReturn(struct hand *hand, struct card *outcard);
void handSort(struct hand *hand, struct card *outcard);
int handDestr(struct hand *hand);

#endif