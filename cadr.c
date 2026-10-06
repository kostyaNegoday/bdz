#include "card.h"

_Bool validcard(struct card c){
    return c.id >= 0 && c.id < CARD;
}

const char rank(struct card c){
    switch(c.id % 13){
        case 0: return "2";
        case 1: return "3";
        case 2: return "4";
        case 3: return "5";
        case 4: return "6";
        case 5: return "7";
        case 6: return "8";
        case 7: return "9";
        case 8: return "10";
        case 9: return "J";
        case 10: return "Q";
        case 11: return "K"; 
        case 12: return "A"; 
    };
}

const char *suit(struct card c){
    switch(c.id / 13){
        case 0: return "Пики";
        case 1: return "Черви";
        case 2: return "Буби";
        case 3: return "Крести";
        default: return "Произошла ошибка, неизвестная масть";
    }
}
