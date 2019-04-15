//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_GAMEPLAY_H
#define UNO_GAMEPLAY_H

#define MAX_PLAYER_NUM 10

extern const void * Gameboard;

enum Direction { CW, CCW };

void show (void * self);
void start (void * self);
void * callPlayers (void * self);
int addCard (void * self, void * card);
void * showStack (void * gameBoard);


#endif //UNO_GAMEPLAY_H
