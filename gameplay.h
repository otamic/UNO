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

void start (void * self);
void * callPlayers (void * self);
void addCard (void * self, void * card);
void randCards (void * self);
int gameover (void * self);

static void ddirection (void * self);
static void next (void * self);
static void addTop (void * self, void * card);
static void addRear (void * self, void * card);
static void drawCard (void * self);


#endif //UNO_GAMEPLAY_H
