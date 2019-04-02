#define DEBUG

#include <stdio.h>
#include "card.h"
#include "new.h"
#include "gameplay.h"
#include "player.h"

#define NUM_PLAYERS 5

int main() {

    int run = 1;
    createCards();
    void * gameboard = new(Gameboard, NUM_PLAYERS);
    start(gameboard);

    while (run) {
        addCard(gameboard, hand(callPlayers(gameboard), gameboard));
        run = gameover(gameboard);
#ifdef DEBUG
        show(gameboard);
#endif
    }

    return 0;
}