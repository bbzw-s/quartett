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

// Utility functions
void eputs(char *);
void nullcheck(void *, char *);
void print_thinkpad(thinkpad *);

// Linked list abstractions
thinkpad *create_thinkpad(char *, int, int, double);
card *create_card(thinkpad *);
cardstack *create_cardstack(card *);
void append_card(cardstack *, card *);
void shuffle_cardstack(cardstack *);
cardstack *split_cardstack(cardstack *);
void next_card(cardstack *);

// Game logic
cardstack *generate_cards(void);
void run_game(void);
void show_game_manual(void);
char start_menu(void);
char select_card_parameter(void);
void play_cards(card *, card *);


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
 * @description initialize a thinkpad struct
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
 * @description initialize a card struct
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

/*
 * @author Lian Studer
 * @description delete the top card from the stack
 */
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
void shuffle_cardstack(cardstack *cs) {
    srand(time(0));
    card *csa[cs->size];

    // load cardstack into card pointer array
    size_t i = 0;
    for(card *cur = cs->head; cur != NULL; cur = cur->next) {
        csa[i] = cur;
        i++;
    }

    // shuffle array
    for (int t = cardstack->size - 1; t > 0; t--) {
        // Pick a random index from 0 to i
        int j = rand() % (t + 1);
 
        // Swap csa with the element at random index
        card temp = csa[t];
        csa[t] = csa[j];
        csa[j] = temp;
    }

    // rethread
    for(int k = 0; k < cardstack->size - 2; k++) {
        if(k == 0) cs->head = csa[k]:
        csa[k]->next = csa[k + 1];
    }
    cs->tail = csa[cardstack->size - 1];
}

/*
 * @author Lian Studer
 * @description generate play cards
 */
cardstack *generate_cards() {
    cardstack *cs = create_cardstack(create_card(create_thinkpad("X220", 8, 256, 2.4)));
    append_card(cs, create_card(create_thinkpad("T420", 8, 512, 2.8)));
    append_card(cs, create_card(create_thinkpad("X60",  8, 64,  1.8)));
    return cs;
}

/*
 * @author Lian Studer
 * @description split the whole stack into two stacks - one for each player
 */
cardstack *split_cardstack(cardstack *cs) {
    int new_stack_size = (int)(cs->size / 2);

    cardstack *new_cardstack = create_cardstack(cs->head);
    nullcheck(new_cardstack, "The second cardstack");

    remove_top_card(cs);
    next_card(cs);

    for (int i = 1; i < new_stack_size; i++) {
        append_card(new_cardstack, cs->head);
        remove_top_card(cs);
        next_card(cs);
    }

    return new_cardstack;
}

/*
 * @author Lian Studer
 */
void print_thinkpad(thinkpad *thinkpad) {
    printf("\n \
╻━━━━━━━━━━━━━━━━━━━━━━╻\n \
┃ Model: %s\t\t┃\n \
┃ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ┃\n \
┃       RAM: %iGb\t┃\n \
┃   Storage: %iGb\t┃\n \
┃ CPU Clock: %.2lfGhz\t┃\n \
╹━━━━━━━━━━━━━━━━━━━━━━╹\n",
    thinkpad->model_name,
    thinkpad->ram,
    thinkpad->storage,
    thinkpad->cpu_clock);
}

/*
 * @author Lian Studer
 */
void play_cards(card *player_top, card *computer_top) {

}

/*
 * @author Lian Studer
 */
void run_game() {
    printf("\n\n--- Starting the game ---\n\n");

    cardstack *computer_stack = generate_cards();
    // shuffle_cardstack(computer_stack);
    cardstack *player_stack = split_cardstack(computer_stack);
    
    while (1) {
        card *player_top = player_stack->head;
        printf("Your card:\n");
        print_thinkpad(player_top->thinkpad);
        
        


        // Game and interaction logic      
        // 1. Select a parameter
        // 2. Keep the card if yours is better, move it to the back of the stack if the other one is better
        // 3. Repeat until one of either stacks is empty
    }
}

/*
 * @author Lian Studer
 */
void show_game_manual() {
    printf("How to play\n\n");
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
    printf("\
░▀█▀░█░█░▀█▀░█▀█░█░█░█▀█░█▀█░█▀▄░░░▄▀▄░█░█░█▀█░█▀▄░▀█▀░█▀▀░▀█▀░▀█▀\n\
░░█░░█▀█░░█░░█░█░█▀▄░█▀▀░█▀█░█░█░░░█ █░█░█░█▀█░█▀▄░░█░░█▀▀░░█░░░█░\n\
░░▀░░▀░▀░▀▀▀░▀░▀░▀░▀░▀░░░▀░▀░▀▀░░░░░▀▀░▀▀▀░▀░▀░▀░▀░░▀░░▀▀▀░░▀░░░▀░\n\n");
    printf("By Kris Huber & Lian Studer\n");

    printf("\n \
Menu\n \
1> Start game\n \
2> How to play\n \
3> Quit\n\n");

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
                exit(0);
                break;
        }
    } 

    return 0;
}
