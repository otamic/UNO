//
// Created by 冯彦澄 on 2019-03-30.
//

#include <stdarg.h>
#include <assert.h>
#include "cardQueue.h"
#include "new.h"

struct CardQueue {
    const void * class;
    void * cards[MAX_CQUEUE_NUM];
    int front, rear;
};

static void * CardQueue_ctor (void * _self, va_list * app) {
    struct CardQueue * self = _self;
    self->front = self->rear = 0;
    return self;
}

static const struct Class _CardQueue = {
      sizeof(struct CardQueue), CardQueue_ctor, 0
};

const void * CardQueue = & _CardQueue;

void qpush (void * _self, void * _card) {
    struct CardQueue * self = _self;
    void * card = _card;

    assert(((self->rear + 1) % MAX_CQUEUE_NUM) != self->front);
    self->cards[self->rear] = card;
    self->rear = (self->rear + 1) % MAX_CQUEUE_NUM;
}

void * qfront (const void * _self) {
    const struct CardQueue * self = _self;

    assert(self->rear != self->front);
    return self->cards[self->front];
}

void * qrear (const void * _self) {
    const struct CardQueue * self = _self;
    int id;

    if (self->rear == self->front)
        return NULL;
    id = (self->rear - 1 + MAX_CQUEUE_NUM) % MAX_CQUEUE_NUM;
    return self->cards[id];
}

void * qpop (void * _self) {
    struct CardQueue * self = _self;

    assert(self->rear != self->front);
    void * card = self->cards[self->front];
    self->front = (self->front + 1) % MAX_CQUEUE_NUM;
    return card;
}

int qlength (const void * _self) {
    const struct CardQueue * self = _self;
    return (self->rear - self->front + MAX_CQUEUE_NUM) % MAX_CQUEUE_NUM;
}

