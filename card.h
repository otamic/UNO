//
// Created by 冯彦澄 on 2019-03-28.
//

#ifndef UNO_CARD_H
#define UNO_CARD_H

#define UNO_CARDS_NUMBER 112
#define COLOR_NUM 6
#define NUMBER_NUM 10
#define SKILL_NUM 5
#define MAX_STRING_SIZE 20

extern const void * Card;
extern const void * NumberCard;
extern const void * SkillCard;
extern void ** allCards;

enum Color { blue = 0, green, red, yellow, nulColor, rdmColor };
enum Number { zero = 0, one, two, three, four, five, six, seven, eight, nine, nulNumber };
enum Skill { skip = 0, reverse, addTwo, addFour, wild };

int isCard(void * card, const void * class);

void setColor (void * card, enum Color color);
enum Color showColor (void * card);
void setNumber (void * card, enum Number number);
enum Number showNumber (void * card);
enum Skill showSkill (void * skillCard);

void printCard(void * card);

/*
 * Call this only once to initialize all basic cards
 */
void createCards();

#endif //UNO_CARD_H
