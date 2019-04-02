//
// Created by 冯彦澄 on 2019-03-30.
//

#include <stdarg.h>
#include <assert.h>
#include "cardStack.h"
#include "new.h"

static void * CardStack_ctor (void * _self, va_list * app) {
    struct CardStack * self = _self;
    self->top = -1;
    return self;
}

static void * CardStack_dtor (void * _self) {
    struct CardStack * self = _self;
    self->top = 0;
    return self;
}

static const struct Class _CardStack = {
    & _CardStack, sizeof(struct CardStack), CardStack_ctor, CardStack_dtor
};

const void * CardStack = & _CardStack;

void spush (void * _self, void * _card) {
    struct CardStack * self = _self;
    struct Card * card = _card;

    assert(self->top != MAX_CSTACK_NUM -1);
    self->cards[++ self->top] = card;
}

void * stop (const void * _self) {
    const struct CardStack * self = _self;

    if (self->top == -1)
        return NULL;
    return self->cards[self->top];
}

void * spop (void * _self) {
    struct CardStack * self = _self;

    assert(self->top != -1);
    return self->cards[self->top --];
}

int slength (const void * _self) {
    const struct CardStack * self = _self;
    return self->top + 1;
}