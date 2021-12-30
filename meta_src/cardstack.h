#ifndef CARDSTACK_H
#define CARDSTACK_H

#include <stdlib.h>

#include "card.h"

typedef struct {
    card *head;
    card *tail;
    size_t size;
} cardstack;

#endif
