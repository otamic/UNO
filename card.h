//
// Created by 冯彦澄 on 2019-03-28.
//

#ifndef UNO_CARD_H
#define UNO_CARD_H

extern const void * Card;
extern const void * NumberCard;
extern const void * SkillCard;

enum Color { blue = 0, green, red, yellow, nulColor };
enum Number { zero = 0, one, two, three, four, five, six, seven, eight, nine, nulNumber };
enum Skill { skip = 0, reverse, addTwo, addFour, wild };

struct Card {
    const void * class;
    enum Color color;
    enum Number number;
};

struct NumberCard {
    const struct Card _;
};

struct SkillCard {
    const struct Card _;
    enum Skill skill;
};

#endif //UNO_CARD_H
