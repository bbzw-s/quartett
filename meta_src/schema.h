#ifndef SCHEMA_H
#define SCHEMA_H

typedef struct _schema {
    char *name;
    struct _schema *next;
} schema;

#endif
