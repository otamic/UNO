//
// Created by 冯彦澄 on 2019-03-28.
//

#include <stdlib.h>
#include <stdio.h>
#include "card.h"
#include "new.h"

static void * Card_ctor (void * _self, va_list * app) {
    struct Card * self = _self;

    self->color = va_arg(* app, enum Color);
    self->number = va_arg(* app, enum Number);
    return self;
}

static const struct Class _Card = {
        & _Card, sizeof(struct Card), Card_ctor, 0
};

const void * Card = & _Card;

static void * NumberCard_ctor (void * _self, va_list * app) {
    return Card_ctor(_self, app);
}

static const struct Class _NumberCard = {
        & _NumberCard, sizeof(struct Card), NumberCard_ctor, 0
};

const void * NumberCard = & _NumberCard;

static void * SkillCard_ctor (void * _self, va_list * app) {
    struct SkillCard * self = ((const struct Class *) Card)->ctor(_self, app);

    self->skill = va_arg(* app, enum Skill);
    return self;
}

static const struct Class _SkillCard = {
        & _SkillCard, sizeof(struct SkillCard), SkillCard_ctor, 0
};

const void * SkillCard = & _SkillCard;

void showCard (void * _card) {
    struct Class * card = _card;
    if (card->obj == NumberCard) {
        printColor(card);
        printNumber(card);
    }
    else {
        struct SkillCard * skillCard = _card;
        switch (skillCard->skill) {
            case skip:
                printColor(skillCard);
                printf("skip ");
                break;
            case reverse:
                printColor(skillCard);
                printf("reverse ");
                break;
            case addTwo:
                printColor(skillCard);
                printf("addTwo ");
                break;
            case addFour:
                printf("addFour ");
                break;
            case wild:
                printf("wild ");
                break;
            default:
                break;
        }
    }
}

static void printColor (void * _card) {
    struct Card * card = _card;
    switch (card->color) {
        case blue:
            printf("blue ");
            break;
        case green:
            printf("green ");
            break;
        case red:
            printf("red ");
            break;
        case yellow:
            printf("yellow ");
        default:
            break;
    }
}

static void printNumber (void * _card) {
    struct Card * card = _card;
    switch (card->number) {
        case zero:
            printf("0 ");
            break;
        case one:
            printf("1 ");
            break;
        case two:
            printf("2 ");
            break;
        case three:
            printf("3 ");
            break;
        case four:
            printf("4 ");
            break;
        case five:
            printf("5 ");
            break;
        case six:
            printf("6 ");
            break;
        case seven:
            printf("7 ");
            break;
        case eight:
            printf("8 ");
            break;
        case nine:
            printf("9 ");
            break;
        default:
            break;
    }
}

void ** allCards;
void createCards () {
    enum Color allColor[4] = { blue, green, red, yellow };
    enum Number allNumber[10] = { zero, one, two, three, four, five, six, seven, eight, nine };

    allCards = (void **) malloc(UNO_CARDS_NUMBER * sizeof(void *));
    int id = 0, i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 10; j++)
            for (k = 0; k < 2; k++, id++)
                allCards[id] = new(NumberCard, allColor[i], allNumber[j]);

    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++, id++)
            allCards[id] = new(SkillCard, allColor[i], nulNumber, skip);

    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++, id++)
            allCards[id] = new(SkillCard, allColor[i], nulNumber, reverse);

    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++, id++)
            allCards[id] = new(SkillCard, allColor[i], nulNumber, addTwo);

    for (i = 0; i < 4; i++, id++)
        allCards[id] = new(SkillCard, nulColor, nulNumber, wild);

    for (i = 0; i < 4; i++, id++)
        allCards[id] = new(SkillCard, nulColor, nulNumber, addFour);
}

void setColor (void * _self, enum Color color) {
    struct Card * self = _self;
    self->color = color;
}