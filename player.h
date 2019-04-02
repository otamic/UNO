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

struct Player {
    const void * class;
    int id;
    int cardsNum;
    void * cards[UNO_CARDS_NUMBER];
    enum Control cTag;
};

void * hand (void * self, void * gameboard);
enum Color choseColor (void * self);
int restCards (void * self);
void getCard (void * self, void * card);
void * putCard (void * self, int id);
void callUNO (void * self);
void catchUNO (void * self, void * other);
#endif //UNO_PLAYER_H
