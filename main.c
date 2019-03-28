#include <stdio.h>
#include "card.h"
#include "new.h"

int main() {
    void * cardA = new(NumberCard, one, red);
    void * cardB = new(SkillCard, one, red, addTwo);

    printf("%d %d", ((struct NumberCard *)cardA)->_.number, ((struct NumberCard *)cardA)->_.color);

    delete(cardA);
    return 0;
}