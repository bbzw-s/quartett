#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

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
void print_thinkpad(cardstack *);

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
char select_menu_option(void);
char select_card_parameter(void);
int play_cards(thinkpad *, thinkpad *);
void print_win();
void print_loss();

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
    nullcheck(first_card, "Thinkpad passed into linked list initializer");
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
//  * @author Kris Huber
//  * @description shuffle all cards in cardstack
//  */
// void shuffle_cardstack(cardstack *cs) {
//     srand(time(0));
//     card **csa = malloc(sizeof(card*) * cs->size);

//     puts("");

//     // load cardstack into card pointer array
//     size_t i = 0;
//     for(card *cur = cs->head; cur != NULL; cur = cur->next) {
//         if(i > cs->size) break;
//         csa[i] = cur;
//         i++;
//     }

//     // shuffle array
//     for (int t = cs->size - 1; t > 0; t--) {
//         // Pick a random index from 0 to i
//         int j = rand() % (t + 1);
 
//         // Swap csa with the element at random index
//         card *temp = csa[t];
//         csa[t] = csa[j];
//         csa[j] = temp;
//     }

//     puts("");

//     // rethread
//     for(int k = 0; k < cs->size - 2; k++) {
//         if(k == 0) cs->head = csa[k];
//         csa[k]->next = csa[k + 1];
//     }
//     puts("");
//     cs->tail = csa[cs->size - 1];
// }

/*
 * @author Lian Studer
 * @description generate play cards
 */
cardstack *generate_cards() {
    cardstack *cs = create_cardstack(create_card(create_thinkpad("X220", 8, 256, 3)));
    append_card(cs, create_card(create_thinkpad("x230", 12, 320, 2.3)));
    append_card(cs, create_card(create_thinkpad("T420", 8, 512, 2.8)));
    append_card(cs, create_card(create_thinkpad("T60", 3, 80, 1.7)));
    append_card(cs, create_card(create_thinkpad("X60",  7, 64,  1.8)));
    append_card(cs, create_card(create_thinkpad("X61", 5, 100, 1.6)));
    append_card(cs, create_card(create_thinkpad("701C", 6, 5, 0.05)));
    append_card(cs, create_card(create_thinkpad("Z61e", 1, 40, 1.1)));
    append_card(cs, create_card(create_thinkpad("235", 9, 14, 0.22)));
    append_card(cs, create_card(create_thinkpad("A22m", 4, 6, 1.5)));
    append_card(cs, create_card(create_thinkpad("R60i", 2, 18, 2.22)));
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
void print_thinkpad(cardstack *cardstack) {
    thinkpad *thinkpad = cardstack->head->thinkpad;
    printf("\n \
+-Your card------------+\n \
| Model: %s\t\t|\n \
| -------------------- |\n \
|       RAM: %iGB\t|\n \
|   Storage: %iGB\t|\n \
| CPU Clock: %.2lfGHz\t|\n \
+----------------------+\n",
    thinkpad->model_name,
    thinkpad->ram,
    thinkpad->storage,
    thinkpad->cpu_clock);
}

/*
 * @author Lian Studer
 */
void print_cardstack_info(cardstack *player_stack, cardstack *computer_stack) {
    printf("\n \
+-Cardstacks-------------------+\n \
|     Your stack size: %i\t|\n \
| Opponent stack size: %i\t|\n \
+------------------------------+\n",
    player_stack->size,
    computer_stack->size);
}

/*
 *  @author Kris Huber
 */
void print_win() {
    puts("+-------------------+");
    puts("| You Won The Game! |");
    puts("+-------------------+");
}

/*
 *  @author Kris Huber
 */
void print_loss() {
    puts("+--------------------+");
    puts("| You Lost The Game! |");
    puts("+--------------------+");
}

/*
 * @author Lian Studer
 * @description compares the players cards based on the selected field, 
 *  returns 0 if the player won or 1 if the computer won
 */
int play_cards(thinkpad *player_thinkpad, thinkpad *computer_thinkpad) {
    printf("\n \
Select a parameter:\n \
1> RAM in GB\n \
2> Storage in GB\n \
3> CPU Clock in GHz\n \
4> Quit\n\n");
    char selected_option = select_menu_option();
    switch (selected_option) {
        case '1':
            if (player_thinkpad->ram > computer_thinkpad->ram)
                return 0;
            else
                return 1;
            break;
        case '2':
            if (player_thinkpad->storage > computer_thinkpad->storage)
                return 0;
            else
                return 1;
            break;
        case '3':
            if (player_thinkpad->cpu_clock > computer_thinkpad->cpu_clock)
                return 0;
            else
                return 1;
            break;
        case '4':
            exit(0);
            break;
    }
}

/*
 * @author Lian Studer
 */
void run_game() {
    cardstack *computer_stack = generate_cards();
    // shuffle_cardstack(computer_stack);
    cardstack *player_stack = split_cardstack(computer_stack);
    
    while (1) {
        thinkpad *computer_thinkpad = computer_stack->head->thinkpad;
        thinkpad *player_thinkpad = player_stack->head->thinkpad;
        
        print_cardstack_info(player_stack, computer_stack);
        print_thinkpad(player_stack);
        
        int result = play_cards(player_thinkpad, computer_thinkpad);
        if (result == 0) { // player wins
            append_card(player_stack, computer_stack->head);
            remove_top_card(computer_stack);
            next_card(player_stack);

            puts("You won this round!");
        } else if (result == 1) { // computer wins
            append_card(computer_stack, player_stack->head);
            remove_top_card(player_stack);
            next_card(computer_stack);
            puts("You lost this round!");
        }

        if (player_stack->size == 0) {
            print_loss();
            return;
        } else if (computer_stack-> size == 0) {
            print_win();
            return;
        }
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
char select_menu_option() {
    char selected_option;
    printf("Enter your selection: ");
    scanf(" %c", &selected_option);
     
    if (isdigit(selected_option)) {
        return selected_option;
    }

    printf("%c is not a valid option\n", selected_option);
    return 0;
}

/*
 * @author Lian Studer
 */
int main() {
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
    printf("ThinkPad?? Quartett\nBy Kris Huber & Lian Studer\n\n");

    printf("\n \
Menu\n \
1> Start game\n \
2> How to play\n \
3> Quit\n\n");

    while (1) {
        char menu_option = select_menu_option();
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

    printf("\n \
Would you like to play again?\n \
y> Yes\n \
n> No\n\n");
    char confirm = select_menu_option();
        switch (confirm) {
            case 'y':
                run_game();
            case 'n':
                exit(0);
                break;
        }

    return 0;
}

