//
// Created by 冯彦澄 on 2019-03-28.
//

#include <stdlib.h>
#include "card.h"
#include "new.h"

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

static void * NumberCard_ctor (void * _self, va_list * app) {
    return Card_ctor(_self, app);
}

static const struct Class _NumberCard = {
        sizeof(struct Card), NumberCard_ctor, 0
};

const void * NumberCard = & _NumberCard;

static void * SkillCard_ctor (void * _self, va_list * app) {
    struct SkillCard * self = ((const struct Class *) Card)->ctor(_self, app);

    self->skill = va_arg(* app, enum Skill);
    return self;
}

static const struct Class _SkillCard = {
        sizeof(struct SkillCard), SkillCard_ctor, 0
};

const void * SkillCard = & _SkillCard;