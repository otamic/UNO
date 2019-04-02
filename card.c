//
// Created by 冯彦澄 on 2019-03-28.
//

#include <stdlib.h>
#include <stdio.h>
#include "card.h"
#include "new.h"

static const char Colors[COLOR_NUM][MAX_STRING_SIZE] = { "blue", "green", "red", "yellow" };
static const char Numbers[NUMBER_NUM][MAX_STRING_SIZE] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char Skills[SKILL_NUM][MAX_STRING_SIZE] = { "skip", "reverse", "addTwo", "addFour", "wild" };

/*
 * class Card
 */
static void * Card_ctor (void * _self, va_list * app) {
    struct Card * self = _self;

    self->color = va_arg(* app, enum Color);
    self->number = va_arg(* app, enum Number);
    return self;
}

static const struct Class _Card = {
        sizeof(struct Card), Card_ctor, 0
};

const void * Card = & _Card;

/*
 * class NumberCard
 */
static void * NumberCard_ctor (void * _self, va_list * app) {
    return Card_ctor(_self, app);
}

static const struct Class _NumberCard = {
        sizeof(struct Card), NumberCard_ctor, 0
};

const void * NumberCard = & _NumberCard;

/*
 * class SkillCard
 */
static void * SkillCard_ctor (void * _self, va_list * app) {
    struct SkillCard * self = ((const struct Class *) Card)->ctor(_self, app);

    self->skill = va_arg(* app, enum Skill);
    return self;
}

static const struct Class _SkillCard = {
        sizeof(struct SkillCard), SkillCard_ctor, 0
};

const void * SkillCard = & _SkillCard;

/*
 * Card method
 */
void showCard (void * _card) {
    struct Card * card = _card;
    if (card->class == NumberCard) {
        printColor(card);
        printNumber(card);
    }
    else {
        struct SkillCard * skillCard = _card;
        printColor(skillCard);
        printf("%s ", Skills[skillCard->skill]);
    }
}

static void printColor (void * _card) {
    struct Card * card = _card;
    if (card->color != nulNumber)
        printf("%s ", Colors[card->color]);
}

static void printNumber (void * _card) {
    struct Card * card = _card;
    if (card->number != nulNumber)
        printf("%s ", Numbers[card->number]);
}

void ** allCards;
void createCards () {
    enum Color allColor[4] = { blue, green, red, yellow };
    enum Number allNumber[10] = { zero, one, two, three, four, five, six, seven, eight, nine };
    enum Skill skillGpOne[3] = { skip, reverse, addTwo };
    enum Skill skiilGpTwo[2] = { wild, addFour };

    allCards = (void **) malloc(UNO_CARDS_NUMBER * sizeof(void *));
    int id = 0, i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 10; j++)
            for (k = 0; k < 2; k++, id++)
                allCards[id] = new(NumberCard, allColor[i], allNumber[j]);

    for (i = 0; i < 4; i++)
        for (k = 0; k < 3; k++)
            for (j = 0; j < 2; j++, id++)
                allCards[id] = new(SkillCard, allColor[i], nulNumber, skillGpOne[k]);

    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++, id++)
            allCards[id] = new(SkillCard, nulColor, nulNumber, skiilGpTwo[j]);
}

void setColor (void * _self, enum Color color) {
    struct Card * self = _self;
    self->color = color;
}

void setNumber (void * _self, enum Number number) {
    struct Card * self = _self;
    self->number = number;
}