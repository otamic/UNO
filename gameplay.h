//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_GAMEPLAY_H
#define UNO_GAMEPLAY_H

#define MAX_PLAYER_NUM 10

extern const void * Gameboard;

enum Direction { CW, CCW };

struct Gameboard {
    const void * class;
    int playerNum;
    int playerNow;
    void ** players;
    enum Direction direction;
    void * cqueue;
    void * cstack;
    int restCards;
};

void show (void * self);
void start (void * self);
void * callPlayers (void * self);
int addCard (void * self, void * card);

static void ddirection (void * self);
static void next (void * self);
static void drawCard (void * self);
static void desort (int * array, int count);


#endif //UNO_GAMEPLAY_H
