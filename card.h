#ifndef CARD
#define CARD
#define CARDCOUNT 52
#define SUITCOUNT 4
#define RANKCOUNT 13
typedef struct {
    int id;
} card;

typedef struct CardNode {
    card card;
    struct CardNode *next;
} CardNode;

int validcard(card card);
int rank(card card); 
int suit(card card); 
int cardsort(card c, card c1);
const char *cardrankname(card card);
const char *cardsuitname(card card);
CardNode *createCardNode(card card);
void freeCardNode(CardNode *node);

#endif
