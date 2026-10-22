#include "game.h"
#include <stdlib.h>
#include <string.h>

static int activeplayer(const player *player) {
    return !player->enough && !player->toomuch; 
}

static int playersCurrent(game *game){
    int count =0;
    for (int i = 0; i<game->numPlayers; ++i){
        if (!game->players[i].toomuch) ++count;
    }
    return count;
}

int bestScore(game *game){
    if (game == NULL || game->players == NULL) return -1;
    int best = -1;
    for (int i = 0; i<game->numPlayers; ++i){
        if (!game->players[i].toomuch){
            int score = handscore(&game->players[i].hand);
            if (score >best) best = score;
        }
    }
    return best;
}

int gameRoundWinner (game *game, int index){
    if (game == NULL || game->players == NULL || index < 0 || index >= game->numPlayers) return 0;
    player *player = &game->players[index];
    int best = bestScore(game);
    return best >=0 && !player->toomuch && handscore(&player->hand) == best;
}

static void finishRound(game *game){
    for (int i =0; i<game->numPlayers;i++){
        if (gameRoundWinner(game,i)) ++game->players[i].wins;
    }
    game->phase = ROUNDOVER;
    game->currentPlayer = -1;
    for (int i = 0; i< game->numPlayers;i++){
        if (game->players[i].wins >= MAXWINS){
            game->phase = GAMEOVER;
        }
    }
}


static void turn(game *game, int prev){
    if(game->deck.count == 0|| playersCurrent(game) <2){
        finishRound(game);
        return;
    }

    for (int offset = 1; offset<=game->numPlayers; ++offset){
        int index = (prev + offset) % game->numPlayers;
        if (activeplayer(&game->players[index])){
            game->currentPlayer = index;
            return;
        }
    }
    finishRound(game);
}

static player *currentActivePlayer(game *game){
    if (game == NULL || !gameValidate(game) || game->phase != PLAYING){
        return NULL;
    }
    return &game->players[game->currentPlayer];
}

void gameDestroy (game *g){
    if (g == NULL) return;
    if (g->players !=NULL) {
        for (int i =0; i< g->numPlayers; i++){
            handclear(&g->players[i].hand);
        }
    }
    free(g->players);
    deckdestroy(&g->deck);
    *g = (game){0};
}

int gameNew(game *g, char *names[], int count){
    if (g == NULL || names == NULL || count < MINPLAYERS ||
        count >MAXPLAYERS||g->players !=NULL||g->deck.top !=NULL||
        g->numPlayers!=0) return GAMEFAILED;
    for (int i = 0; i<count;i++){
        if (names[i] == NULL || strlen(names[i])>=MAXNAME || strpbrk(names[i], "\r\n") != 0) return GAMEFAILED;
    }
    game fresh = {0};
    fresh.players = calloc((size_t)count, sizeof *fresh.players);
    if (fresh.players == NULL) return NOMEMORY;
    fresh.numPlayers = count;
    fresh.phase = PLAYING;
    fresh.currentPlayer = 0;
    
    for (int i = 0; i<count; i++){
        strcpy(fresh.players[i].name, names[i]);
        handinit(&fresh.players[i].hand);
    }
    if (!deckinit(&fresh.deck) || !deckshuffle(&fresh.deck)){
        gameDestroy(&fresh);
        return NOMEMORY;
    }

    for (int i =0; i< count;++i){
        handsorted(&fresh.players[i].hand, deckdraw(&fresh.deck));
    }
    *g = fresh;
    return GAMEOK;
}

int gameDraw(game *g){
    player *player = currentActivePlayer(g);
    if(player == NULL)return GAMEFAILED;
    CardNode *node =deckdraw(&g->deck);
    if (node == NULL) return GAMEFAILED;
    handsorted(&player->hand,node);
    int score = handscore(&player->hand);
    if(score>21){
        player->toomuch = 1;
        deckbottom(&g->deck, handtakeall(&player->hand));
    } else if(score==21){
        player->enough = 1;
    }
    turn(g,g->currentPlayer);
    return GAMEOK;
}

int gameStand(game *g){
    player *player = currentActivePlayer(g);
    if(player == NULL) return GAMEFAILED;
    player->enough = 1;
    turn(g, g->currentPlayer);
    return GAMEOK;
}


int gameShuffle(game *g){
    if(g == NULL||!gameValidate(g)||g->phase!=PLAYING) return GAMEFAILED;
    return deckshuffle(&g->deck) ? GAMEOK : NOMEMORY;
}

int gameNextround(game *g){
    if (g == NULL||!gameValidate(g)||g->phase!=ROUNDOVER) return GAMEFAILED;
    char *names[MAXPLAYERS];
    for(int i = 0; i<g->numPlayers;++i)names[i]=g->players[i].name;
    game fresh = {0};
    int res = gameNew(&fresh,names,g->numPlayers);
    if(res!=GAMEOK) return res;
    for (int i=0; i<g->numPlayers;++i) fresh.players[i].wins = g->players[i].wins;
    gameDestroy(g);
    *g = fresh;
    return GAMEOK;
}

static int checkCardList(CardNode *head, int seen[CARDCOUNT], int sorted, CardNode **last){
    int lengh = 0;
    *last = NULL;
    for (CardNode *node = head; node!=NULL; node = node->next){
        int id = node->card.id;
        if (id<0||id>=CARDCOUNT||seen[id]++) return -1;
        if(sorted&&*last!=NULL&&cardsort((*last)->card, node->card)>0) return -1;
        *last = node;
        if(++lengh >CARDCOUNT) return -1;
    }
    return lengh;

}

int gameValidate(game *g){
    if (g == NULL||g->players==NULL||g->numPlayers<MINPLAYERS||
    g->numPlayers>MAXPLAYERS||g->phase<PLAYING||
    g->phase>GAMEOVER) return 0;
    int seen[CARDCOUNT] = {0};
    CardNode *last;
    int total = checkCardList(g->deck.top, seen, 0, &last);
    if (total !=g->deck.count||last!=g->deck.bottom) return 0;
    int matchWinner = 0;
    int active = 0;
    for(int i =0; i<g->numPlayers;++i){
        player *player = &g->players[i];
        if(memchr(player->name, '\0', MAXNAME)==NULL||
            player->wins<0||player->wins>MAXWINS||
            (player->enough!=0&&player->enough!=1)||
            (player->toomuch!=0&&player->toomuch!=1)||
            (player->enough&&player->toomuch)) return 0;
        if (player->wins>=MAXWINS) matchWinner = 1;
        if (activeplayer(player)) active = 1;

        int handCount = checkCardList(player->hand.head, seen, 1, &last);
        if(handCount<0||handCount!=player->hand.count) return 0;
        if(player->toomuch? handCount!=0 : handCount==0||handscore(&player->hand)>21) return 0;
        total+=handCount;
    }

    if(total!=CARDCOUNT) return 0;
    if (g->phase == PLAYING) {
        if(matchWinner||!active||g->deck.count==0) return 0;
        if(g->currentPlayer<0||g->currentPlayer>=g->numPlayers) return 0;
        if(!activeplayer(&g->players[g->currentPlayer])) return 0;
    } else {
        if(g->currentPlayer!=-1) return 0;
        if((g->phase==GAMEOVER)!=matchWinner) return 0;
    }
    return 1;
}
