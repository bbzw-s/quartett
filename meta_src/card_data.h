#ifndef CARD_DATA_H
#define CARD_DATA_H

#include <stdlib.h>

typedef union {
    char *STRING;
    int INT;
    float FLOAT;
} card_data_data;

typedef enum {
    String,
    Int,
    Float
} card_data_tag;

typedef struct _card_data {
    card_data_data data;
    card_data_tag tag;
    struct _card_data *next;
} card_data;

typedef struct {
    card_data *head;
    card_data *tail;
    size_t size;
} card_data_list;

// functions to use from outside
card_data_list *create_card_data_list(card_data_data*, card_data_tag*);
void append_card_data(card_data_list*, card_data_data*, card_data_tag*);
// TODO: free, remove node, shuffle

// helper functions
void *create_card_data(card_data_data*, card_data_tag*);

#endif
