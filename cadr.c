#include "card.h"
#include <stdlib.h>

int validcard(card card) {
    return (card.id >= 0 && card.id < CARDCOUNT);
}

int rank(card card) {
    return card.id % RANKCOUNT;
}

int suit(card card) {
    return card.id / RANKCOUNT;
}

int cardsort(card c, card c1) {
    int rank1 = rank(c);
    int rank2 = rank(c1);
    if (rank1 != rank2) return (rank1>rank2) - (rank1<rank2);
    return (suit(c) > suit(c1)) - (suit(c) < suit(c1));
}

char *cardrankname(card card) {
    char *names[RANKCOUNT] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    return names[rank(card)];
}

char *cardsuitname(card card) {
    char *names[SUITCOUNT] = {"Черви", "Бубны", "Крести", "Пики"};
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
    if (node != NULL) {
        CardNode *next = node->next;
        free(node);
    }
}