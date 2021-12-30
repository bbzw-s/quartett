#ifndef LINKED_H
#define LINKED_H

typedef enum {
    Card,
    CardList,
    Cardstack,
    CardData,
    Schema
} linked_type;

// functions to use from outside
void *create_linked(linked_type, void*);
void append_node(linked_type, void*, void*);
void dump_linked(linked_type, void*);
char *stringify_linked_type(linked_type);
// TODO: free, remove node, shuffle

// helper functions (should only be used from linked.c
void *create_node(linked_type, void*);

#endif
