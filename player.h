//
// Created by 冯彦澄 on 2019-03-30.
//

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include "card.h"

extern const void * Player;

#ifndef ENUM_CONTROL
#define ENUM_CONTROL
enum Control { computer = 0, man };
#endif

void * hand (void * player, void * gameboard);

void getCard (void * player, void * card);
enum Color choseColor (void * player);
void * putCard (void * player, int id);

int restCards (void * player);
enum Control getControl (void * player);
int getId (void * player);
void * ownCards (void * player, int i);

void callUNO (void * player);
void catchUNO (void * player, void * other);
#endif //UNO_PLAYER_H
