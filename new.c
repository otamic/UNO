//
// Created by 冯彦澄 on 2019-03-28.
//

#include <stdlib.h>
#include <assert.h>
#include "new.h"

void * new (const void * _class, ...) {
    const struct Class * class = _class;
    void * p = calloc(1, class->size);

    assert(p);
    * (const struct Class **) p = class;

    if (class->ctor) {
        va_list ap;

        va_start(ap, _class);
        p = class->ctor(p, & ap);
        va_end(ap);
    }
    return p;
}

void delete (void * self) {
    const struct Class ** cp = self;

    if (self && * cp && (* cp)->dtor)
        self = (* cp)->dtor(self);
    free(self);
}