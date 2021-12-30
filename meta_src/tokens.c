#include <stdbool.h>
#include <string.h>

#include "tokens.h"

bool is_valid_token(char *s) {
    if(
        !strcmp(s, SCHEMA)
        || !strcmp(s, CARD)
        || !strcmp(s, LPAREN)
        || !strcmp(s, RPAREN)
        || !strcmp(s, SET)
    ) {
        return (true);
    }
    return (false);
}

const char *token_stringify(token t) {
     switch(t) {
        case Schema: return "Schema";
        case Card:   return "Card";
        case Lparen: return "Lparen";
        case Rparen: return "Rparen";
        case Set:    return "Set";
        case None:   return "None";
     }
}
