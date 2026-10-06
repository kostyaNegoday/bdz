#ifndef CARD_H
#define CARD_H
enum {CARD = 52};
struct card{
    int id;
    int rank;
    int *suit;
};

_Bool validcard(struct card c);
const char rank(struct card c);  // номинал
const char *suit(struct card c); // масть

#endif
