#include "deck.h"
#include <stdlib.h>

int deckinit(deck *deck){
    if (deck == NULL || deck->top !=NULL) return 0;
    for (int id =0; id<CARDCOUNT; ++id){
        CardNode *node = createCardNode((card){id});
        if (node == NULL) {
            deckdestroy(deck);
            return 0;
        }
    }
    return 1;
}

CardNode *deckdraw(deck *deck) {
    if (deck == NULL ||deck->top == NULL) return NULL;
    CardNode *node = deck->top;
    deck->top = node->next;
    if (deck->top == NULL) deck->bottom == NULL;
    node->next = NULL;
    --deck->count;
    return node;
}

void deckbottom (deck *deck, CardNode *chain){
    if (deck == NULL) return;
    while (chain!=NULL){
        CardNode *next = chain->next;
        chain->next = NULL;
        if (deck->bottom == NULL){
            deck->top = chain;
            deck->bottom = chain;
        } else {
            deck->bottom->next = chain;
        }
        deck->bottom = chain;
        ++deck->count;
        chain = next;
    }
}

int deckshuffle(deck *deck){
    if (deck == NULL) return 0;
    if (deck->count < 2) return 1;
    CardNode **nodes = malloc((size_t)deck->count * sizeof(CardNode *));
    if (nodes == NULL) return 0;
    int n = 0;
    for (CardNode *node = deck->top; node != NULL && n<deck->count; node = node->next){
        nodes[n++] = node;
    }
    for(int i = n - 1; i > 0; --i){
        int j = rand() % (i + 1);
        CardNode *tmp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = tmp;
    }

    for (int i =0; i<n;i++) nodes[i]->next = nodes[i+1];
    nodes[n-1]->next = NULL;
    deck->top = nodes[0];
    deck->bottom = nodes[n-1];
    free(nodes);
    return 1;
}

void deckdestroy(deck *deck){
    if (deck == NULL) return;
    freeCardNode(deck->top);
    deck->top = NULL;
    deck->bottom = NULL;
    deck->count = 0;
}