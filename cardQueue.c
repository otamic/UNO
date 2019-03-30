//
// Created by 冯彦澄 on 2019-03-30.
//

#include <stdarg.h>
#include <assert.h>
#include "cardQueue.h"
#include "new.h"

static void * CardQueue_ctor (void * _self, va_list * app) {
    struct CardQueue * self = _self;
    self->front = self->rear = 0;
    return self;
}

static void * CardQueue_dtor (void * _self) {
    struct CardQueue * self = _self;
    self->front = self->rear = 0;
    return self;
}

static const struct Class _CardQueue = {
      & _CardQueue, sizeof(struct CardQueue), CardQueue_ctor, CardQueue_dtor
};

const void * CardQueue = & _CardQueue;

void qpush (void * _self, void * _card) {
    struct CardQueue * self = _self;
    struct Card * card = _card;

    assert(((self->rear + 1) % MAX_CQUEUE_NUM) != self->front);
    self->cards[self->rear] = card;
    self->rear = (self->rear + 1) % MAX_CQUEUE_NUM;
}

void * qtop (const void * _self) {
    const struct CardQueue * self = _self;

    assert(self->rear != self->front);
    return self->cards[self->front];
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

