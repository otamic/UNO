//
// Created by 冯彦澄 on 2019-03-30.
//

#ifndef DEBUG
#define DEBUG
#endif

#ifdef DEBUG
#include <stdio.h>
#endif

#include <assert.h>
#include <stdarg.h>
#include "player.h"
#include "new.h"
#include "monitor.h"
#include "cardStack.h"
#include "gameplay.h"

struct Player {
    const void * class;
    int id;
    int cardsNum;
    void * cards[UNO_CARDS_NUMBER];
    enum Control cTag;
};

static void * Player_ctor (void * _self, va_list * app) {
    struct Player * self = _self;
    self->cardsNum = 0;
    self->cTag = va_arg(* app, enum Control);
    self->id = va_arg(* app, int);
    return self;
}

static const struct Class _Player = {
        sizeof(struct Player), Player_ctor, 0
};

const void * Player = & _Player;

// 人工控制和手动输入可变为静态全局的
void * hand (void * _self, void * _gameboard) {
    struct Player * self = _self;
    void * gameboard = _gameboard;

    void * frontCard = stop(showStack(gameboard));
    void * resCard = mhand(self, frontCard);

#ifdef DEBUG
    if (resCard) {
        printf("Player%d has put: ", self->id);
        showCard(resCard);
    }
    else
        printf("Player%d didn't put a card!", self->id);
    printf("\n\n");
#endif

    return resCard;
}

enum Color choseColor (void * _self) {
    struct Player * self = _self;

    enum Color resCol = mChoseColor(self);
    return resCol;
}

int restCards (void * _self) {
    struct Player * self = _self;

    int rest = self->cardsNum;
    return rest;
}

void getCard (void * _self, void * _card) {
    struct Player * self = _self;
    struct Card * card = _card;

    self->cards[self->cardsNum++] = card;
}

void * putCard (void * _self, int id) {
    struct Player * self = _self;
    int i;

    assert(id < self->cardsNum);
    void * pCard = self->cards[id];
    for (i = id; i < self->cardsNum - 1; i++)
        self->cards[i] = self->cards[i + 1];
    -- self->cardsNum;
    return pCard;
}

enum Control getControl (void * _self) {
    struct Player * self = _self;
    return self->cTag;
}

int getId (void * _self) {
    struct Player * self = _self;
    return self->id;
}

void * ownCards (void * _self, int i) {
    struct Player * self = _self;
    return self->cards[i];
}

void callUNO (void * _self) {

}

void catchUNO (void * _self, void * _other) {

}