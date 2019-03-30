#include <stdio.h>
#include "card.h"
#include "new.h"
#include "gameplay.h"
#include "player.h"

#define NUM_PLAYERS 2

int main() {

    int run = 1;

    while (run) {
        void * gameboard = new(Gameboard, NUM_PLAYERS);
        randCards(gameboard);

        start(gameboard);
        addCard(gameboard, hand(callPlayers(gameboard), gameboard));
        run = gameover(gameboard);
    }

    return 0;
}