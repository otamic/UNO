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

void * mhand(void * player, void * frontCard);
enum Color mChoseColor (void * player);



#endif //UNO_MONITOR_H
