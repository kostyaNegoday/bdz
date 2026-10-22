#ifndef GAME
#define GAME
#include "deck.h"
#include "hand.h"

#define MAXPLAYERS 10
#define MINPLAYERS 2
#define MAXNAME 64
#define MAXWINS 5
#define PLAYING 0
#define ROUNDOVER 1
#define GAMEOVER 2
#define GAMEOK 1
#define GAMEFAILED 0
#define NOMEMORY -1
#define EMPTYDECK -2

typedef struct {
    char name[MAXNAME];
    hand hand;
    int wins;
    int enough;
    int toomuch;
} player;

typedef struct{
    player *players;
    int numPlayers;
    deck deck;
    int phase;
    int currentPlayer;
} game;

int gameNew(game *game, char *names[], int count);
int gameDraw(game *game);
int gameStand(game *game);
int gameShuffle(game *game);
int gameNextround(game *game);
int bestScore(game *game);
int gameRoundWinner(game *game, int index);
int gameValidate(game *game);
void gameDestroy(game *game);

#endif
