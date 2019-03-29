//
// Created by 冯彦澄 on 2019-03-28.
//

#ifndef UNO_NEW_H
#define UNO_NEW_H

#include <stdarg.h>
#include <zconf.h>

struct Class {
    const void * obj;
    size_t size;
    void * (* ctor) (void * self, va_list * app);
    void * (* dtor) (void * self);
};

void * new (const void * class, ...);
void delete (void * self);

#endif //UNO_NEW_H
