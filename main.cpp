#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * Quartett Projekt
 * von Kris Huber & Lian Studer
 */

/*
 * ~~~ Headers Section ~~~
 */
#ifndef CONFIG_H
#define CONFIG_H

#include "cardstack.h"
#include "schema.h"

// misc constants
#define CARDS_CONFIG "data/thinkpad.cards"
#define MAX_SCHEMA_SIZE 16
#define SCHEMA_BUF_SIZE 64

typedef struct {
    cardstack *cs;
    schema *scm;
} config;

#endif

#ifndef UTIL_H
#define UTIL_H

void eputs(char*);
void nullcheck(void*, char*);

#endif

#ifndef CARD_H
#define CARD_H

#include "card_data.h"

typedef struct _card {
     card_data *data;
    struct _card *next;
} card;

#endif

#ifndef CARDSTACK_H
#define CARDSTACK_H

#include <stdlib.h>

#include "card.h"

typedef struct {
    card *head;
    card *tail;
    size_t size;
} cardstack;

#endif

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

#ifndef PARSER_H
#define PARSER_H

#include "linked.h"

linked *parse();

#endif

#ifndef SCHEMA_H
#define SCHEMA_H

typedef struct _schema {
    char *name;
    struct _schema *next;
} schema;

#endif


/*
 * ~~~ Source Section ~~~
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * @author Kris Huber
 * @description stderr fprintf wrapper
 */
void eputs(char *s) {
    fprintf(stderr, "%s\n", s);
}

/*
 * @author Kris Huber
 * @description simple null checking procedure
 */
void nullcheck(void *ptr, char *msg) {
    if(ptr != NULL) return;
    fprintf(stderr, "Error (Unexpected Null Value): %s\n", msg);
    exit(1);
}

/*
 * @author Kris Huber
 */
bool is_number(char *s) {
    bool is_number = true;
    for(char *x = s; is_number && *x != '\0'; ++x) {
        if(!(*x >= '0' && *x <= '9')) is_number = false;
    }
    return is_number;
}


/*
 * ~~~ Main ~~~
 */
#include <stdio.h>

/*
 * Main Function
 */
int main() {
    puts("prototype");

    return 0;
}

