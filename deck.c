#include "deck.h"
#include <stdlib.h>

int deckInit(struct deck *deck){
    if(deck == NULL) return 1;
    deck->count = 0;
    deck->masscount = CARD;
    for(int i = 0; i < CARD; i++){
        deck->cards[i] = i;
    }
    return 0;
}

void deckSort(struct deck *deck){

}