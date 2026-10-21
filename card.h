#ifndef CARD_H
#define CARD_H
#define CARDCOUNT 52
#define SUITCOUNT 4
#define RANKCOUNT 13
typedef struct {
    int id;
} card;

typedef struct{
    card card;
    CardNode *next;
} CardNode;

int validcard(card card);
int rank(card card); 
int suit(card card); 
int cardsort(card c, card c1);
char *cardrankname(card card);
char *cardsuitname(card card);
CardNode *createCardNode(card card);
void freeCardNode(CardNode *node);
#endif