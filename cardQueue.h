//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_CARDQUEUE_H
#define UNO_CARDQUEUE_H

#include "card.h"

#define MAX_CQUEUE_NUM (UNO_CARDS_NUMBER * 2)

extern const void * CardQueue;

struct CardQueue {
    const void * class;
    struct Card * cards[MAX_CQUEUE_NUM];
    int front, rear;
};

void qpush (void * self, void * Card);
void * qfront (const void * self);
void * qrear (const void * self);
void * qpop (void * self);
int qlength (const void * self);


#endif //UNO_CARDQUEUE_H
