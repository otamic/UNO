//
// Created by 冯彦澄 on 2019-03-31.
//

#ifndef UNO_MONITOR_H
#define UNO_MONITOR_H

#include "card.h"

extern const void * Monitor;

#ifndef ENUM_CONTROL
#define ENUM_CONTROL
enum Control { computer = 0, man };
#endif

struct Monitor {
    const void * class;
    enum Control cTag;
    void * (* mhand) (void * player, void * frontCard);
    enum Color (* mchoseColor) (void * player);
};

static void * hand_com (void * player, void * frontCard);
static void * hand_man (void * player, void * frontCard);
static enum Color chose_com (void * player);
static enum Color chose_man (void * player);

static int checkCard (void * card, void * frontCard);


#endif //UNO_MONITOR_H
