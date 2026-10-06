#include "deck.h"
#include <stdlib.h>

int deckInit(struct deck *deck){
    if(deck == NULL) return 1;
    deck->count = 0;
    deck->masscount = CARD;
    for(int i = 0; i < CARD; i++){
        deck->cards[i].id = i;
    }
    return 0;
}

int deckGivecard(struct deck *deck, struct card *outcard) {
    if (deck == NULL || outcard == NULL || deck->cards == NULL) return 1;
    if (deck->count <= 0) return 2; /* колода пуста */
    deck->count--;
    *outcard = deck->cards[deck->count];
    return 0;
}

int deckReturn(struct deck *deck, struct card *outcard) {
    if (deck == NULL || outcard == NULL || deck->cards == NULL) return 1;
    if (deck->count >= deck->masscount) return 2; /* колода полна */
    deck->cards[deck->count] = *outcard;
    deck->count++;
    return 0;
}   

void deckSort(struct deck *deck, struct card *outcard) {
    if (deck == NULL || outcard == NULL || deck->cards == NULL) return;
    for (int i = 0; i < deck->count - 1; i++) {
        for (int j = i + 1; j < deck->count; j++) {
            if (deck->cards[i].id > deck->cards[j].id) {
                struct card temp = deck->cards[i];
                deck->cards[i] = deck->cards[j];
                deck->cards[j] = temp;
            }
        }
    }
}

int deckDestr(struct deck *deck) {
    if (deck == NULL) return 1;
    free(deck->cards);
    deck->cards = NULL;
    deck->count = 0;
    deck->masscount = 0;
    return 0;
}