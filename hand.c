#include "hand.h"
#include <stdlib.h>

void handinit(hand *hand) {
    hand->head = NULL;
    hand->count = 0;
}

int handsorted(hand *hand, CardNode *node) {
    if (hand ==  NULL || node == NULL || !validcard(node->card)) return 1;
    CardNode **place = &hand->head;
    while (*place != NULL && cardsort((*place)->card, node->card) < 0) {
        place = &(*place)->next;
    }
    node ->next = *place;
    *place = node;
    ++hand->count;
    return 1;
}   

int handscore(hand *hand) {
    if (hand == NULL) return 0;
    int score = 0;
    int ace = 0;
    for (CardNode *node = hand->head; node!=NULL; node = node->next){
       int rank  = cardrank(node->card);
       if (rank == 0) return -1;
       if (rank == 14){
        score += 11;
        ace++;
       } else if (rank >=10) {
        score += 10;
       } else {
        score += rank;
       }
    }
    while (score > 21 && ace > 0) {
        score -= 10;
        ace--;
    }
    return score;
}   

CardNode *handtakeall(hand *hand) {
    if (hand == NULL) return NULL;
    CardNode *head = hand->head;
    handinit(hand);
    return head;
}

void handclear(hand *hand){
    if (hand ==NULL) return NULL;
    freeCardNode(hand->head);
    handinit(hand);
}