#include "hand.h"
#include <stdlib.h>

int handInit(struct hand *hand) {
    if (hand == NULL) return 1;
    hand->count = 0;
    hand->masscount = CARD;
    for (int i = 0; i < CARD; i++) {
        hand->cards[i].id = i;
    }
    return 0;
}

int handGivecard(struct hand *hand, struct card *outcard) {
    if (hand == NULL || outcard == NULL || hand->cards == NULL) return 1;
    if (hand->count == 0) return 2; 
    hand->count--;
    *outcard = hand->cards[hand->count];
    return 0;
}

int handScore(struct hand *hand, struct card *outcard) {
    if (hand == NULL || outcard == NULL || hand->cards == NULL) return 1;
    int score = 0;
    for (int i = 0; i < hand->count; i++) {
        score += hand->cards[i].rank;
    }
    *outcard = (struct card){.id = -1, .rank = score};
    return 0;
}