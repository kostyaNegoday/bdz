#ifndef CARD_H
#define CARD_H
enum {CARD = 52};
struct card{
    int id;
    int rank;
    int *suit;
};

_Bool validcard(struct card c);
int rank(struct card c);  // номинал
int *suit(struct card c); // масть

#endif
