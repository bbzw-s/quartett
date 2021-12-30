#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "tokens.h"
#include "util.h"
#include ""

linked *parse() {
    char buffer[SCHEMA_BUF_SIZE];
    token current = None;
    char schema[MAX_SCHEMA_SIZE][SCHEMA_BUF_SIZE];
    short schema_size = 0;
    short schema_current = 0;
    bool schema_filled = false;
    bool in_schema = false;
    bool in_card = false;
    bool in_set = false;
    linked *list = init_linked(ht_create());

    FILE *cards = fopen(CARDS_CONFIG, "r");
    nullcheck(cards, "Card Configuration File Path");

    while(fscanf(cards, "%s", &buffer) == true) {
        // validating tokens and assigning them to current token enum
             if(strcmp(buffer, SCHEMA)  == 0)   { current = Schema; }
        else if(strcmp(buffer, CARD)    == 0)   { current = Card;   }
        else if(strcmp(buffer, LPAREN)  == 0)   { current = Lparen; }
        else if(strcmp(buffer, RPAREN)  == 0)   { current = Rparen; }
        else if(strcmp(buffer, SET)     == 0)   { current = Set;    }
        else                                    { current = None;   }

        if(current != None) {
            switch(current) {
                case Schema:
                    in_schema = true;
                break;
                
                case Card:
                    in_card = true;
                break;

                case Set:
                    in_set = true;
                break;

                case Rparen:
                    in_schema = in_card = in_set = false;
                break;

                default:
                    continue;
                break;
            }
        } else if(in_schema || in_card || in_set) {
            if(in_schema && in_set) {
                strcpy(schema[schema_size], buffer);
                schema_size++;
            }
            if(in_card && in_set) {
                if(schema_filled) append_node(list, ht_create());
                ht_set(list->tail->data, schema[schema_current], buffer);

                if(schema_current < schema_size - 1) {
                    schema_current++;
                    if(schema_filled) schema_filled = false;
                } else {
                    schema_current = 0;
                    if(!schema_filled) schema_filled = true;
                }
            }
        } else {
            eputs("Error (Cards Parser): Invalid Token");
        }
    }

    if(schema_current != 0) eputs("Error (Cards Parser): Set Statements Don't Match Schema");

    return list;
}
