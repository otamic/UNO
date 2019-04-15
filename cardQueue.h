//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef UNO_CARDQUEUE_H
#define UNO_CARDQUEUE_H

#include "card.h"

#define MAX_CQUEUE_NUM (UNO_CARDS_NUMBER * 2)

extern const void * CardQueue;

void qpush (void * queue, void * Card);
void * qfront (const void * queue);
void * qrear (const void * queue);
void * qpop (void * queue);
int qlength (const void * queue);


#endif //UNO_CARDQUEUE_H
