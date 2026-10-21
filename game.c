#include "game.h"
#include <stdlib.h>
#include <stdio.h>


int gameInit(struct game *game, int numPlayers, char *playerNames[]) {
    if (game == NULL) return 1;
    printf("введите количество игроков (от 2 до 10): \n");
    scanf("%d", &numPlayers);
    if (numPlayers < 2 || numPlayers > 10) return 1;
    game->numPlayers = numPlayers;
    return 0;
}

int playerInit(struct player *player, struct game *g) {
    if (player == NULL) return 1;
    for (int i = 0; i < g->numPlayers; i++) {
        printf("Игрок %d, введите свое имя: \n", i + 1);
        scanf(" %49s", player->name);
    }
    return 0;
}


int gameStart(struct game *game) {
    return 0;
}

int gamePlay(struct game *game) {
    return 0;
}

int gameEnd(struct game *game) {
    return 0;
}

int deckShuffle(struct deck *deck) {
    return 0;
}

void gameDestroy(struct game *game) {
}