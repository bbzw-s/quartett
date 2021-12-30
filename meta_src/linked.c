#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "card_data.h"
#include "linked.h"

void *create_linked(linked_type type, void *data) {
    nullcheck(data, "Data Passed into LL Initializer");

    switch(type) {
        case Card:
            break;

        case CardList:
            break;

        case Cardstack:
            break;

        case CardData: {
            card_data_list *l = malloc(sizeof(card_data_list));
            l->tail = l->head = create_node(CardData, data);
            l->size = 1;
            return l;
        }

        case Schema:
            break;

        default:
            break;
    }

    return NULL;
}

void *create_node(linked_type type, void *data) {
    nullcheck(data, "Data Passed into Node Initializer");

    switch(type) {
        case Card:
            break;

        case CardList:
            break;

        case Cardstack:
            break;

        case CardData: {
            card_data *n = malloc(sizeof(card_data));

            switch(n->data_tag) {
                case String:
                    n->data.STRING = (char*)data;
                    break;
                case Int:
                    n->data.INT = *(int*)data;
                    break;
                case Double:
                    n->data.DOUBLE = *(double*)data;
                    break;
            }
            n->next = NULL;
            return n;
        }

        case Schema:
            break;

        default:
            eputs("Couldn't create node");
            break;
    }

    return NULL;
}

void append_node(linked_type type, void *list, void *data) {
    nullcheck(data, "Data Passed into Node Appender");

    switch(type) {
        case Card:
            break;

        case CardList:
            break;

        case Cardstack:
            break;

        case CardData: {
            card_data_list *l = (card_data_list*)list;
            l->tail = l->tail->next = create_node(type, data);
            l->size++;

            break;
        }

        case Schema:
            break;

        default:
            eputs("Couldn't create node");
            break;
    }
}

void dump_linked(linked_type type, void *list) {
    switch(type) {
        case Card:
            break;

        case CardList:
            break;

        case Cardstack:
            break;

        case CardData: {
            card_data_list *l = (card_data_list*)list;
            size_t i = 1;
            for(card_data *c = l->head; c != NULL; c = c->next) {
                printf("Data of Node(%s) [%zu/%zu]\n", stringify_linked_type(type), i, l->size);
                // TODO: data printing
                i += 1;
            }
            break;
        }

        case Schema:
            break;

        default:
            eputs("Couldn't dump node");
            break;
    }
}

char *stringify_linked_type(linked_type type) {
    switch(type) {
        case Card:      return "Card";
        case CardList:  return "CardList";
        case Cardstack: return "Cardstack";
        case CardData:  return "CardData";
        case Schema:    return "Schema";
    }

    return NULL;
}
