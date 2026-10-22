#include "card.h"
#include <stdlib.h>

int validcard(card card) {
    return (card.id >= 0 && card.id < CARDCOUNT);
}

int rank(card card) {
    if (!validcard(card)) return 0;
    return card.id % RANKCOUNT + 2;
}

int suit(card card) {
    if (!validcard(card)) return -1;
    return card.id / RANKCOUNT;
}

int cardsort(card c, card c1) {
    int rank1 = rank(c);
    int rank2 = rank(c1);
    if (rank1 != rank2) return (rank1>rank2) - (rank1<rank2);
    return (suit(c) > suit(c1)) - (suit(c) < suit(c1));
}

const char *cardrankname(card card) {
    static const char *names[RANKCOUNT] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    if (!validcard(card)) return "?";
    return names[rank(card) - 2];
}

const char *cardsuitname(card card) {
    static const char *names[SUITCOUNT] = {"Черви", "Бубны", "Крести", "Пики"};
    if (!validcard(card)) return "?";
    return names[suit(card)];
}

CardNode *createCardNode(card card) {
    if (!validcard(card)) return NULL;
    CardNode *node = malloc(sizeof *node);
    if (node == NULL) return NULL;
    node->card = card;
    node->next = NULL;
    return node;
}

void freeCardNode(CardNode *node) {
    while (node != NULL) {
        CardNode *next = node->next;
        free(node);
        node = next;
    }
}
