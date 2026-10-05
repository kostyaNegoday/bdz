#ifndef CARD_H
#define CARD_H
enum {CARD = 52};
struct card{
    int id;
    int rank;
    char *suit;
};

_Bool validcard(struct card c);
int rank(struct card c);  // номинал
char *suit(struct card c); // масть

#endif
