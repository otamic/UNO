//
// Created by 冯彦澄 on 2019-03-31.
//

#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include "monitor.h"
#include "new.h"
#include "player.h"

struct Monitor {
//    const void * class;
    enum Control cTag;
    void * (* m_hand) (void * player, void * frontCard);
    enum Color (* m_choseColor) (void * player);
};

static void * hand_com (void * player, void * frontCard);
static void * hand_man (void * player, void * frontCard);
static enum Color chose_com (void * player);
static enum Color chose_man (void * player);
static int checkCard (void * card, void * frontCard);

static void * hand_com (void * _player, void * _frontCard) {
    struct Player * player = _player;
    void * card = _frontCard;
    int i;

    if (! card)
        return putCard(player, 0);

    void * ownCard;
    for (i = 0; i < restCards(player); i++) {
        ownCard = ownCards(player, i);
        if (showColor(ownCard) == showColor(card))
            return putCard(player, i);
    }
    if (isCard(card, NumberCard)) {
        for (i = 0; i < restCards(player); i++) {
            ownCard = ownCards(player, i);
            if (showNumber(ownCard) == showNumber(card))
                return putCard(player, i);
        }
    }
    else {
        void * skillCard = _frontCard;
        void * ownSkillCard;
        for (i = 0; i < restCards(player); i++) {
            ownSkillCard = ownCards(player, i);
            if (showSkill(ownSkillCard) == showSkill(skillCard))
                return putCard(player, i);
        }
        for (i = 0; i < restCards(player); i++) {
            ownSkillCard = ownCards(player, i);
            if (showSkill(ownSkillCard) == wild || showSkill(ownSkillCard) == addFour)
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
    for (i = 0; i < restCards(player); i++) {
        printf("%d: ", i);
        showCard(ownCards(player, i));
        printf("\n");
    }
    printf("%d: out\n", restCards(player));

    do {
//        printf("Please put your choice: ");
        scanf("%d", &chosed);
        if (chosed == restCards(player))
            break;
        assert(chosed < restCards(player));
    } while (checkCard(ownCards(player, chosed), card));

    if (chosed == restCards(player))
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
    void * card = _card;
    void * frontCard = _frontCard;

    if (!frontCard)
        return 0;
    if (showColor(card) == showColor(frontCard))
        return 0;
    if (isCard(card, NumberCard) &&
            isCard(frontCard, NumberCard) &&
                    showNumber(card) == showNumber(frontCard))
        return 0;
    if (isCard(card, SkillCard) &&
            isCard(frontCard, SkillCard) &&
            showSkill(card) == showSkill(frontCard))
        return 0;
    if (isCard(card, SkillCard) &&
            (showSkill(card) == wild || showSkill(card) == addFour))
        return 0;

    return 1;
}

static const struct Monitor manMonitor = {
        man, hand_man, chose_man
};

static const struct Monitor comMonitor = {
        computer, hand_com, chose_com
};

void * mhand (void * player, void * frontCard) {
    switch (getControl(player)) {
        case man:
            return manMonitor.m_hand(player, frontCard);
        case computer:
            return comMonitor.m_hand(player, frontCard);
    }
}

enum Color mChoseColor (void * player) {
    switch (getControl(player)) {
        case man:
            return manMonitor.m_choseColor(player);
        case computer:
            return comMonitor.m_choseColor(player);
    }
}