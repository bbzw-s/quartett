#ifndef CARD_DATA_H
#define CARD_DATA_H

#include <stdlib.h>

typedef struct _card_data {
    union {
        char *STRING;
        int INT;
        double DOUBLE;
    } data;
    enum {
        String,
        Int,
        Double
    } data_tag;
    struct _card_data *next;
} card_data;

typedef struct {
    card_data *head;
    card_data *tail;
    size_t size;
} card_data_list;

#endif
