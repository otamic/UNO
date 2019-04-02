//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_CARDSTACK_H
#define UNO_CARDSTACK_H

#include "card.h"

#define MAX_CSTACK_NUM UNO_CARDS_NUMBER

extern const void * CardStack;

struct CardStack {
    const void * class;
    struct Card * cards[UNO_CARDS_NUMBER];
    int top;
};

void spush (void * self, void * card);
void * stop (const void * self);
void * spop (void * self);
int slength (const void * self);

#endif //UNO_CARDSTACK_H
