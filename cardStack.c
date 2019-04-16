//
// Created by 冯彦澄 on 2019-03-30.
//

#include <stdarg.h>
#include <assert.h>
#include "cardStack.h"
#include "new.h"

struct CardStack {
    const void * class;
    void * cards[UNO_CARDS_NUMBER];
    int top;
};

static void * CardStack_ctor (void * _self, va_list * app) {
    struct CardStack * self = _self;
    self->top = -1;
    return self;
}

static const struct Class _CardStack = {
    sizeof(struct CardStack), CardStack_ctor, 0
};

const void * CardStack = & _CardStack;

void spush (void * _self, void * card) {
    struct CardStack * self = _self;

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