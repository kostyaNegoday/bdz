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

void deckSort(struct deck *deck){
    (void)deck;
}