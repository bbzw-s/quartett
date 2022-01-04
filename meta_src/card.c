#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "card.h"

card_list *create_card_list(card_data_data *data, card_data_tag *tag) {
    nullcheck(data, "Data Passed into CL Initializer");
    card_data_list *l = malloc(sizeof(card_data_list));
    l->tail = l->head = create_card_data(data, tag);
    l->size = 1;
    return l;
}

card *create_card(card_data_data *data) {
    nullcheck(data, "Data Passed into Card Initializer");
    card *n = malloc(sizeof(card));
    n->data = data;
    n->next = NULL;
    return n;
}

void append_card(card_list *list, card_data *data) {
    nullcheck(data, "Data Passed into Card Appender");
    list->tail = list->tail->next = create_card(data);
    list->size++;
}
