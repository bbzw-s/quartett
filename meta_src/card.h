#ifndef CARD_H
#define CARD_H

#include "card_data.h"

typedef struct _card {
     card_data *data;
    struct _card *next;
} card;

#endif
