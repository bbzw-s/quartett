#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Function Prototypes
 */
void eputs(char *);
void nullcheck(void *, char *);
thinkpad *create_thinkpad(char *, int, int, double);
card *create_card(thinkpad *);
cardstack *create_cardstack(thinkpad *);
card *create_card(thinkpad *);
void append_card(cardstack *, thinkpad *);
cardstack *shuffle_cardstack();
void generate_cards(void);
bool run_game(void);

/*
 * Type Definitions
 */
typedef struct {
    char *model_name;
    int ram;            // RAM in GB
    int storage;        // Storage in GB
    double cpu_clock;   // CPU clock in GHz
} thinkpad;

typedef struct _card {
    thinkpad *thinkpad;
    struct _card *next;
} card;

typedef struct {
    card *head;
    card *tail;
    size_t size;
} cardstack;

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
 * @author Lian Studer
 */
thinkpad *create_thinkpad(char *name, int ram, int storage, double cpu_clock) {
    thinkpad *new_thinkpad = (thinkpad *)malloc(sizeof(thinkpad));
    new_thinkpad->model_name = name;
    new_thinkpad->ram = ram;
    new_thinkpad->storage = storage;
    new_thinkpad->cpu_clock = cpu_clock;
    return new_thinkpad;
}

/*
 * @author Kris Huber
 * @description initialize a cardstack struct
 */
cardstack *create_cardstack(thinkpad *tp) {
    nullcheck(tp, "Thinpad Passed into LL Initializer");
    cardstack *l = malloc(sizeof(cardstack));
    l->tail = l->head = create_node(tp);
    l->size = 1;
    return l;
}

/*
 * @author Kris Huber
 * @description helper function - should never interface directly
 */
card *create_card(thinkpad *tp) {
    card *c = malloc(sizeof(card));
    c->thinkpad = tp;
    c->next = NULL;
    return c;
}

/*
 * @author Kris Huber
 * @description append a card to the cardstack instance
 */
void append_card(cardstack *cs, thinkpad *tp) {
    cs->tail = cs->tail->next = create_card(tp);
    cs->size++;
}

/*
 * @author Kris Huber
 * @description shuffle all cards in cardstack
 */
void shuffle_cardstack(cardstack *cs) {
    card *current = cs-> head;

    // generate distinct set of random numbers in range of 1..cardstack->size

    while(*current != NULL) {
        
        current = current->next;
    }
}

/*
 * @author Lian Studer
 */
void generate_cards() {
    cardstack *cs = create_cardstack(create_card(create_thinkpad("X220", 8, 256, 2.4)));
    append_card(cs, create_card(create_thinkpad("T420", 8, 512, 2.8)));
    append_card(cs, create_card(create_thinkpad("X60",  8, 64,  1.8)));
}

/*
 * @author Lian Studer
 */
bool run_game() { 
    return true;
}

/*
 * @author Lian Studer
 */
int main() {
    return 0;
}
