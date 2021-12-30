#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>

/*
 * Tokens
 */

#define SCHEMA  "schema"
#define CARD    "card"
#define LPAREN  "("
#define RPAREN  ")"
#define SET     "-"

typedef enum {
    Schema,
    Card,
    Lparen,
    Rparen,
    Set,
    None
} token;

bool is_valid_token(char *);
const char *token_stringify(token);

#endif
