//
// Created by 冯彦澄 on 2019-03-29.
//

#ifndef DEBUG
#define DEBUG
#endif

#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef TEST
#define TEST
#endif

#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "gameplay.h"
#include "new.h"
#include "cardQueue.h"
#include "cardStack.h"
#include "player.h"

struct Gameboard {
    const void * class;
    int playerNum;
    int playerNow;
    void ** players;
    enum Direction direction;
    void * cqueue;
    void * cstack;
    int restCards;
};

static void ddirection (void * self);
static void next (void * self);
static void drawCard (void * self);
static void desort (int * array, int count);

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
#ifdef TEST
    self->players[0] = new(Player, man, 0);
    for (i = 1; i < self->playerNum; i++)
        self->players[i] = new(Player, computer, i);
#endif
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
        sizeof(struct Gameboard), Gameboard_ctor, Gameboard_dtor
};

const void * Gameboard = & _Gameboard;

void * callPlayers (void * _self) {
    struct Gameboard * self = _self;

    return self->players[self->playerNow];
}

int addCard (void * _self, void * card) {
    struct Gameboard * self = _self;

    if (restCards(callPlayers(self)) == 0) {
        void * player = callPlayers(self);
#ifdef DEBUG
        printf("Game over! The winner is player%d\n", getId(player));
#endif
        return 0;
    }

    if (card == 0) {
        drawCard(self);
        next(self);
    }
    else {
        if (slength(self->cstack)) {
            void * frontNowCard = stop(self->cstack);
            if (isCard(frontNowCard, NumberCard) ||
               (isCard(frontNowCard, SkillCard) &&
               showSkill(frontNowCard) != addFour && showSkill(frontNowCard) != addTwo
                       && showNumber(frontNowCard) == nulNumber)) {
               qpush(self->cqueue, spop(self->cstack));
            }
        }
        spush(self->cstack, card);
        if (isCard(card, NumberCard)) {
            next(self);
        }
        else {
            switch (showSkill(card)) {
                case skip:
                    next(self);
                    getCard(callPlayers(self), self->cqueue);
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

static void drawCard (void * _self) {
    struct Gameboard * self = _self;
    void * player = callPlayers(self);
    void * cardQueue = self->cqueue;
    void * cardStack = self->cstack;
    void * tcard = stop(cardStack);

    while (slength(cardStack)) {
        void * card = spop(cardStack);
        int i;

        if (isCard(card, SkillCard)) {
            switch (showSkill(card)) {
                case addTwo:
                    if (showNumber(card) == nulNumber) {
                        setNumber(card, zero);
                        for (i = 0; i < 2; i++)
                            getCard(player, qpop(cardQueue));
                    }
                    break;
                case addFour:
                    if (showNumber(card) == nulNumber) {
                        setNumber(card, zero);
                        for (i = 0; i < 4; i++)
                            getCard(player, qpop(cardQueue));
                    }
                    break;
                default:
                    break;
            }
        }
    }
    spush(cardStack, tcard);
    getCard(player, qpop(cardQueue));
}

void start (void * _self) {
    struct Gameboard * self = _self;
    int i, j, numList[UNO_CARDS_NUMBER];

    createCards();
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
#ifdef DEBUG
    srand(0);
#endif
#ifndef DEBUG
    srand((unsigned) time(0));
#endif
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

void showGameboard(void *_self) {
    struct Gameboard * self = _self;
    int i;
    for (i = 0; i < self->playerNum; i++)
        printf("Player%d: %d\n", i, restCards(self->players[i]));
    printf("Front card: ");
    printCard(stop(self->cstack));
    printf("\n\n");
}

void * getStack(void * _self) {
    struct Gameboard * self = _self;
    return self->cstack;
}

void play (void * gameboard) {
    int run = 1;
    while (run) {
        run = addCard(gameboard, hand(callPlayers(gameboard), gameboard));
#ifdef DEBUG
        if (run)
            showGameboard(gameboard);
#endif
    }
}