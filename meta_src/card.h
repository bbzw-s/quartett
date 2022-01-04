#ifndef CARD_H
#define CARD_H

#include "card_data.h"

typedef struct _card {
    card_data_list *data;
    struct _card *next;
} card;

typedef struct {
    card *head;
    card *tail;
    size_t size;
} card_list;

#endif
