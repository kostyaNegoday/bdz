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