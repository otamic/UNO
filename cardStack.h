//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_CARDSTACK_H
#define UNO_CARDSTACK_H

#include "card.h"

#define MAX_CSTACK_NUM UNO_CARDS_NUMBER

extern const void * CardStack;

void spush (void * stack, void * card);
void * stop (const void * stack);
void * spop (void * stack);
int slength (const void * stack);

#endif //UNO_CARDSTACK_H
