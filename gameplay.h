//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_GAMEPLAY_H
#define UNO_GAMEPLAY_H

#define MAX_PLAYER_NUM 10

extern const void * Gameboard;

enum Direction { CW, CCW };

void start (void * gameBoard);
void play (void * gameBoard);

void * callPlayers (void * gameBoard);
void * getStack(void * gameBoard);
int addCard (void * gameBoard, void * card);

void showGameboard(void * gameBoard);


#endif //UNO_GAMEPLAY_H
