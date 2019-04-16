//
// Created by 冯彦澄 on 2019-03-31.
//
#ifndef DEBUG
#define DEBUG
#endif

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

static void * hand_com (void * player, void * frontCard) {
    int i;

    if (! frontCard)
        return putCard(player, 0);

    void * ownCard;
    for (i = 0; i < restCards(player); i++) {
        ownCard = ownCards(player, i);
        if (showColor(ownCard) == showColor(frontCard))
            return putCard(player, i);
    }
    if (isCard(frontCard, NumberCard)) {
        for (i = 0; i < restCards(player); i++) {
            ownCard = ownCards(player, i);
            if (showNumber(ownCard) == showNumber(frontCard))
                return putCard(player, i);
        }
    }
    else {
        for (i = 0; i < restCards(player); i++) {
            ownCard = ownCards(player, i);
            if (showSkill(ownCard) == showSkill(frontCard))
                return putCard(player, i);
        }
        for (i = 0; i < restCards(player); i++) {
            ownCard = ownCards(player, i);
            if (showSkill(ownCard) == wild || showSkill(ownCard) == addFour)
                return putCard(player, i);
        }
    }
    return NULL;
}

static void * hand_man (void * player, void * frontCard) {
    int i, chosed;

    printf("Now you have cards:\n");
    for (i = 0; i < restCards(player); i++) {
        printf("%d: ", i);
        printCard(ownCards(player, i));
        printf("\n");
    }
    printf("%d: out\n", restCards(player));

    do {
//        printf("Please put your choice: ");
        scanf("%d", &chosed);
        if (chosed == restCards(player))
            break;
        assert(chosed < restCards(player));
    } while (checkCard(ownCards(player, chosed), frontCard));

    if (chosed == restCards(player))
        return NULL;
    else
        return putCard(player, chosed);
}

static enum Color chose_com (void * player) {
#ifdef DEBUG
    return blue;
#endif

#ifndef DEBUG
    /* *** */
#endif
}

static enum Color chose_man (void * player) {
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

static int checkCard (void * card, void * frontCard) {
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