#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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
 * Function Prototypes
 */
void eputs(char *);
void nullcheck(void *, char *);
thinkpad *create_thinkpad(char *, int, int, double);
card *create_card(thinkpad *);
cardstack *create_cardstack(card *);
card *create_card(thinkpad *);
void append_card(cardstack *, card *);
void shuffle_cardstack(cardstack *);
cardstack *generate_cards(void);
void run_game(void);
void show_game_manual(void);
char start_menu(void);
cardstack *split_cardstack(cardstack *);
void next_card(cardstack *);

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
cardstack *create_cardstack(card *first_card) {
    nullcheck(first_card, "Thinpad Passed into LL Initializer");
    cardstack *l = malloc(sizeof(cardstack));
    l->tail = l->head = first_card;
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
void append_card(cardstack *cs, card *new_card) {
    cs->tail = cs->tail->next = new_card;
    cs->tail->next = cs->head;
    cs->size++;
}

void remove_top_card(cardstack *cardstack) {
    cardstack->head = cardstack->head->next;
    cardstack->tail->next = cardstack->head;
    cardstack->size--;
}

/*
 * @author Lian Studer
 * @description append a card to the cardstack instance
 */
void next_card(cardstack *cs) {
    cs->tail = cs->head;
    cs->head = cs->head->next;
}

/*
 * @author Kris Huber
 * @description shuffle all cards in cardstack
 */
// void shuffle_cardstack(cardstack *cs) {
//     card *current = cs-> head;

//     // generate distinct set of random numbers in range of 1..cardstack->size

//     while(*current != NULL) {
        
//         current = current->next;
//     }
// }

/*
 * @author Lian Studer
 */
cardstack *generate_cards() {
    cardstack *cs = create_cardstack(create_card(create_thinkpad("X220", 8, 256, 2.4)));
    append_card(cs, create_card(create_thinkpad("T420", 8, 512, 2.8)));
    append_card(cs, create_card(create_thinkpad("X60",  8, 64,  1.8)));
    return cs;
}

cardstack *split_cardstack(cardstack *cs) {
    int first_stack_size = (int)(cs->size / 2);
    int sec_stack_size = (cs->size) - first_stack_size;

    printf("Stack Size 1: %i\n", first_stack_size);
    printf("Stack Size 2: %i\n", sec_stack_size);

    cardstack *new_cardstack = create_cardstack(cs->head);
    nullcheck(new_cardstack, "The second cardstack");

    remove_top_card(cs);
    next_card(cs);


    for (int i = 1; i < first_stack_size; i++) {
        append_card(new_cardstack, cs->head);
        remove_top_card(cs);
        next_card(cs);
    }

    return new_cardstack;
}

/*
 * @author Lian Studer
 */
void run_game() {
    printf("\n\n--- Starting the game ---\n\n");

    cardstack *initial_cardstack = generate_cards();
    printf("Cardstack Size: %i\n", initial_cardstack->size);
    // shuffle_cardstack(initial_cardstack);
    cardstack *second_cardstack = split_cardstack(initial_cardstack);
    printf("Cardstack Size 1: %i\n", initial_cardstack->size);
    printf("Cardstack Size 2: %i\n", second_cardstack->size);
    

    while (1) {
        // Game and interaction logic        
    }
}

/*
 * @author Lian Studer
 */
void show_game_manual() {
    printf("\n\n--- How to play ---\n\n");
}

/*
 * @author Lian Studer
 */
char start_menu() {
    char selected_option;
    printf("Enter your selection: ");
    scanf(" %c", &selected_option);
     
    if (isdigit(selected_option)) {
        return selected_option;
    }

    printf("%c is not a valid menu option\n", selected_option);
    return 0;
}

/*
 * @author Lian Studer
 */
int main() {
    // ASCII ThinkPad Logo
    printf("\n \
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n \
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n \
@@@..........@...@@@@@@@////@@@@@@@@@@@...@@@@@@@.......@@@@@@@@@@@@@@@@@...@@@\n \
@@@@@@....@@@@...@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@...@@...@@@@@@@@@@@@@@@@...@@@\n \
@@@@@@....@@@@........@@...@@........@@...@@...@@...@@...@........@@........@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...@...@@@...@@...@...@@...@@...@@...@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...@...@@@.......@@...@....@@...@@...@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...,..@@@@...,*@@@@@.......@@...@@...@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...@...@@@...@@@@@@...@@...@@...@@...@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...@...@@@...@@@@@@...@@...@@...@@...@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...@@...@@...@@@@@@...@@...@@...@@...@@@\n \
@@@@@@....@@@@...@@...@@...@@...@@...@@...@@...@@...@@@@@@....@...@@....@...@@@\n \
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n \
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
    printf("ThinkPad® Quartett\nBy Kris Huber & Lian Studer\n\n");

    printf("\n \
Menu\n \
1> Start game\n \
2> How to play\n \
3> Quit\n");

    while (1) {
        char menu_option = start_menu();
        switch (menu_option) {
            case '0':
                continue;
            case '1':
                run_game();
                break;
            case '2':
                show_game_manual();
                break;
            case '3':
                break;
        }
    } 

    return 0;
}
