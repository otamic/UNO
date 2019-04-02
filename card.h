//
// Created by 冯彦澄 on 2019-03-28.
//

#ifndef UNO_CARD_H
#define UNO_CARD_H

#define UNO_CARDS_NUMBER 112

extern const void * Card;
extern const void * NumberCard;
extern const void * SkillCard;
extern void ** allCards;

enum Color { blue = 0, green, red, yellow, nulColor, rdmColor };
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

void setColor (void * self, enum Color color);
void setNumber (void * self, enum Number number);
void showCard (void * card);
static void printColor (void * card);
static void printNumber (void * card);
void createCards();

#endif //UNO_CARD_H
