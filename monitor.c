//
// Created by 冯彦澄 on 2019-03-31.
//

#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include "monitor.h"
#include "new.h"
#include "player.h"

static void * Monitor_dtor (void * _self, va_list * app) {
    struct Monitor * self = _self;

    self->cTag = va_arg(* app, enum Control);
    if (self->cTag == computer) {
        self->mhand = hand_com;
        self->mchoseColor = chose_com;
    }
    else {
        self->mhand = hand_man;
        self->mchoseColor = chose_man;
    }
    return self;
}

static const struct Class _Monitor = {
        & _Monitor, sizeof(struct Monitor), Monitor_dtor, 0
};

const void * Monitor = & _Monitor;

static void * hand_com (void * _player, void * _frontCard) {
    struct Player * player = _player;
    struct Card * card = _frontCard;
    int i;

    if (! card)
        return putCard(player, 0);

    struct Card * ownCard;
    for (i = 0; i < player->cardsNum; i++) {
        ownCard = player->cards[i];
        if (ownCard->color == card->color)
            return putCard(player, i);
    }
    if (((struct Class *) _frontCard)->obj == NumberCard) {
        for (i = 0; i < player->cardsNum; i++) {
            ownCard = player->cards[i];
            if (ownCard->number == card->number)
                return putCard(player, i);
        }
    }
    else {
        struct SkillCard * skillCard = _frontCard;
        struct SkillCard * ownSkillCard;
        for (i = 0; i < player->cardsNum; i++) {
            ownSkillCard = player->cards[i];
            if (ownSkillCard->skill == skillCard->skill)
                return putCard(player, i);
        }
        for (i = 0; i < player->cardsNum; i++) {
            ownSkillCard = player->cards[i];
            if (ownSkillCard->skill == wild || ownSkillCard->skill == addFour)
                return putCard(player, i);
        }
    }
    return NULL;
}

static void * hand_man (void * _player, void * _frontCard) {
    struct Player * player = _player;
    struct Card * card = _frontCard;
    int i, chosed;

    printf("Now you have cards:\n");
    for (i = 0; i < player->cardsNum; i++) {
        printf("%d: ", i);
        showCard(player->cards[i]);
        printf("\n");
    }
    printf("%d: out\n", player->cardsNum);

    do {
//        printf("Please put your choice: ");
        scanf("%d", &chosed);
        if (chosed == player->cardsNum)
            break;
        assert(chosed < player->cardsNum);
    } while (checkCard(player->cards[chosed], card));

    if (chosed == player->cardsNum)
        return NULL;
    else
        return putCard(player, chosed);
}

static enum Color chose_com (void * _player) {
    struct Player * player = _player;
    return blue;
}

static enum Color chose_man (void * _player) {
    struct Player * player = _player;
    int chosed;

    printf("Please chose a color: 1.blue 2.green 3.red 4.yellow\n");
    scanf("%d", & chosed);
    assert(chosed < 5 && chosed > 0);

    switch (chosed) {
        case 1:
            return blue;
        case 2:
            return green;
        case 3:
            return red;
        case 4:
            return yellow;
        default:
            break;
    }
}

static int checkCard (void * _card, void * _frontCard) {
    struct Card * card = _card;
    struct Card * frontCard = _frontCard;

    if (!frontCard)
        return 0;
    if (card->color == frontCard->color)
        return 0;
    if (((struct Class *) _card)->obj == NumberCard &&
            ((struct Class *) _frontCard)->obj == NumberCard &&
                    card->number == frontCard->number)
        return 0;
    if (((struct Class *) _card)->obj == SkillCard &&
            ((struct Class *) _frontCard)->obj == SkillCard &&
            ((struct SkillCard *) _card)->skill == ((struct SkillCard *) _frontCard)->skill)
        return 0;
    if (((struct Class *) _card)->obj == SkillCard &&
            (((struct SkillCard *) _card)->skill == wild || ((struct SkillCard *) _card)->skill == addFour))
        return 0;

    return 1;
}