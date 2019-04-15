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

void * hand (void * self, void * gameboard);
enum Color choseColor (void * self);
int restCards (void * self);
void getCard (void * self, void * card);
void * putCard (void * self, int id);
enum Control getControl (void * player);
int getId (void * player);
void * ownCards (void * player, int i);
void callUNO (void * self);
void catchUNO (void * self, void * other);
#endif //UNO_PLAYER_H
