//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef DEBUG
#define DEBUG
#endif

#include <stdio.h>

#include <stdarg.h>
#include <stdlib.h>
#include "gameplay.h"
#include "new.h"
#include "cardQueue.h"
#include "cardStack.h"
#include "player.h"

static void * Gameboard_ctor (void * _self, va_list * app) {
    struct Gameboard * self = _self;
    int numOfPlayers = va_arg(* app, int);
    int i;

    self->playerNum = numOfPlayers;
    self->playerNow = 0;
    self->direction = CW;
    self->cqueue = new(CardQueue);
    self->cstack = new(CardStack);
    self->restCards = UNO_CARDS_NUMBER;

    self->players = (void **) malloc(self->playerNum * sizeof(void *));
    self->players[0] = new(Player, man, 0);
    for (i = 1; i < self->playerNum; i++)
        self->players[i] = new(Player, computer, i);

    return self;
}

static void * Gameboard_dtor (void * _self) {
    struct Gameboard * self = _self;
    int i;

    for (i = 0; i < self->playerNum; i++)
        delete(self->players[i]);
    free(self->players);
    delete(self->cstack);
    delete(self->cqueue);

    return self;
}

static const struct Class _Gameboard = {
        & _Gameboard, sizeof(struct Gameboard), Gameboard_ctor, Gameboard_dtor
};

const void * Gameboard = & _Gameboard;

void * callPlayers (void * _self) {
    struct Gameboard * self = _self;

    return self->players[self->playerNow];
}

int addCard (void * _self, void * _card) {
    struct Gameboard * self = _self;
    struct Class * card = _card;

    if (restCards(callPlayers(self)) == 0) {
        struct Player * player = callPlayers(self);
#ifdef DEBUG
        printf("Game over! The winner is player%d\n", player->id);
#endif
        return 0;
    }

    if (_card == 0) {
        drawCard(self);
        next(self);
    }
    else {
        if (slength(self->cstack))
            addRear(self, spop(self->cstack));
        addTop(self, card);
        if (card->obj == NumberCard) {
            next(self);
        }
        else {
            struct SkillCard * skillCard = _card;
            switch (skillCard->skill) {
                case skip:
                    next(self);
                    drawCard(self);
                    next(self);
                    break;
                case reverse:
                   ddirection(self);
                   next(self);
                   break;
                case addTwo:
                    next(self);
                    break;
                case addFour:
                case wild:
                    setColor(stop(self->cstack), choseColor(callPlayers(self)));
                    next(self);
                    break;
            }
        }
    }
    return 1;
}

static void ddirection (void * _self) {
    struct Gameboard * self = _self;
    if(self->direction == CW)
        self->direction = CCW;
    else
        self->direction = CW;
}

static void next (void * _self) {
    struct Gameboard * self = _self;

    if (self->direction == CW) {
        self->playerNow = (self->playerNow + 1) % self->playerNum;
    }
    else
        self->playerNow = (self->playerNow - 1 + self->playerNum) % self->playerNum;
}

static void addTop (void * _self, void * _card) {
    struct Gameboard * self = _self;
    struct Card * card = _card;

    spush(self->cstack, card);
}

static void addRear (void * _self, void * _card) {
    struct Gameboard * self = _self;
    struct Card * card = _card;

    qpush(self->cqueue, card);
}

static void drawCard (void * _self) {
    struct Gameboard * self = _self;
    struct Player * player = callPlayers(self);
    struct CardQueue * cardQueue = self->cqueue;
    struct CardStack * cardStack = self->cstack;

    while (1) {
        struct Class * card = stop(self->cstack);
        int i;

        if (card->obj == NumberCard) {
            getCard(player, qpop(cardQueue));
        } else {
            struct SkillCard * skillCard = (struct SkillCard *) card;
            switch (skillCard->skill) {
                case skip:
                case reverse:
                case wild:
                    getCard(player, qpop(cardQueue));
                    break;
                case addTwo:
                    for (i = 0; i < 2; i++)
                        getCard(player, qpop(cardQueue));
                    break;
                case addFour:
                    for (i = 0; i < 4; i++)
                        getCard(player, qpop(cardQueue));
                    break;
            }
        }

        if (slength(cardStack) == 1)
            break;
    }
}

void start (void * _self) {
    struct Gameboard * self = _self;
    int i, j, numList[UNO_CARDS_NUMBER];

    for (i = 0; i < UNO_CARDS_NUMBER; i++)
        numList[i] = i;
    desort(numList, UNO_CARDS_NUMBER);
    for (i = 0; i < UNO_CARDS_NUMBER; i++)
        qpush(self->cqueue, allCards[numList[i]]);

    for (i = 0; i < self->playerNum; i++)
        for (j = 0; j < 7; j++)
            getCard(self->players[i], qpop(self->cqueue));
}

#define RAND_LOOP 10000
#define RAND_CONSTANT_A 10

static void desort (int * array, int count) {
    srand(0);
    int i, j, interval;
    for (i = 0; i < RAND_LOOP; i++) {
        interval = rand() % (rand() % RAND_CONSTANT_A + 1) + 1;
        int loop = count - interval, mid = array[interval];
        for (j = interval; j < loop; j += interval)
            array[j] = array[j+interval];
        array[j] = mid;
    }
    interval = array[0];
    array[0] = array[count - 1];
    array[count - 1] = interval;
}

void show (void * _self) {
    struct Gameboard * self = _self;
    int i;
    for (i = 0; i < self->playerNum; i++)
        printf("Player%d: %d\n", i, restCards(self->players[i]));
    printf("Front card: ");
    showCard(stop(self->cstack));
    printf("\n\n");
}