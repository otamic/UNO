#define DEBUG

#include <stdio.h>

#include "new.h"
#include "gameplay.h"


#define NUM_PLAYERS 5

int main() {

    void * gameboard = new(Gameboard, NUM_PLAYERS);
    start(gameboard);
    play(gameboard);
    delete(gameboard);

    return 0;
}