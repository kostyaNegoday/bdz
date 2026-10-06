#ifndef GAME
#define GAME

#include "deck.h"
#include "hand.h"

struct player {
    char name[50];
    struct hand hand;
    int score;
    int wins;
    int enough;
    int determinated;
};

struct game {
    struct player *players;
    int numPlayers;
    struct deck deck;
    int phase;
    int currPlayer;
};

int playerInit(struct player *player, char *name);
int gameInit(struct game *game, int numPlayers, char *playerNames[]);
int gameStart(struct game *game);
int gamePlay(struct game *game);
int gameEnd(struct game *game);
int deckShuffle(struct deck *deck);
void gameDestroy(struct game *game);

#endif