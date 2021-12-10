// ThinkPad Quartett

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *model_name;
    int ram;            // RAM in Gb
    int storage;        // Storage in Gb
    double cpu_clock;   // CPU clock in Ghz
} thinkpad_t;

typedef struct card {
    thinkpad_t *thinkpad;
    struct card *next;
    struct card *prev;
} card_t;

typedef struct {
    card_t *top_card;

} talon_t;

/*
 * @author Lian Studer
 */
card_t *new_card(thinkpad_t *model) {
    card_t *new_card = (card_t *)malloc(sizeof(card_t));
    new_card->thinkpad = model;
    new_card->next = NULL; 
    return new_card;
}

/*
 * @author Lian Studer
 */
thinkpad_t *new_thinkpad(char *name, int ram, int storage, double cpu_clock) {
    thinkpad_t *new_thinkpad = (thinkpad_t *)malloc(sizeof(thinkpad_t));
    new_thinkpad->model_name = name;
    new_thinkpad->ram = ram;
    new_thinkpad->storage = storage;
    new_thinkpad->cpu_clock = cpu_clock;
    return new_thinkpad;
}

/*
 * @author Lian Studer
 */
card_t *generate_cards() {
    card_t *head = NULL;

    thinkpad_t *thinkpad1 = new_thinkpad("X220", 8, 256, 2.4);
    card_t *card1 = new_card(thinkpad1);
    head = card1;

    thinkpad_t *thinkpad2 = new_thinkpad("X420", 8, 512, 2.8);
    card_t *card2 = new_card(thinkpad2);
    head->next = card2;
    head = card2;

    thinkpad_t *thinkpad3 = new_thinkpad("T60", 4, 64, 1.8);
    card_t *card3 = new_card(thinkpad3);
    head->next = card3;
    head = card3;

    head->next = card1;
    return card1;
}

/*
 * @author Lian Studer
 */
bool run_game() {
    card_t *full_stack = _generate_dummy_data();
}

/*
 * @author Lian Studer
 */
int main() {
    card_t *head = _generate_dummy_data();

    for (int i = 0; i < 10; i++) {
        printf("ThinkPad Model: %s\n", head->thinkpad->model_name);
        head = head->next;
    }

    return 0;
}
