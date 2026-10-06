#include "card.h"

_Bool validcard(struct card c){
    return c.id >= 0 && c.id < CARD;
}

int rank(struct card c){
    switch(c.id % 13){
        case 0: return 2;
        case 1: return 3;
        case 2: return 4;
        case 3: return 5;
        case 4: return 6;
        case 5: return 7;
        case 6: return 8;
        case 7: return 9;
        case 8: return 10;
        case 9: return 11;
        case 10: return 12;
        case 11: return 13; 
        case 12: return 14; 
    };
}

int *suit(struct card c){
    switch(c.id / 13){
        case 0: return 1;
        case 1: return 2;
        case 2: return 3;
        case 3: return 4;
    }
}
