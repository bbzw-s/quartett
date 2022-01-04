#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "card_data.h"

card_data_list *create_card_data_list(card_data_data *data, card_data_tag *tag) {
    nullcheck(data, "Data Passed into CDL Initializer");
    card_data_list *l = malloc(sizeof(card_data_list));
    l->tail = l->head = create_card_data(data, tag);
    l->size = 1;
    return l;
}

card_data *create_card_data(card_data_data *data, card_data_tag *tag) {
    nullcheck(data, "Data Passed into CD Initializer");
    card_data *n = malloc(sizeof(card_data));
    n->data = *data;
    n->tag  = *tag;
    n->next = NULL;
    return n;
}

void append_card_data(card_data_list *list, card_data_data *data, card_data_tag *tag) {
    nullcheck(data, "Data Passed into CD Appender");
    list->tail = list->tail->next = create_card_data(data, tag);
    l->size++;
}
