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
