// ThinkPad Quartett

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *model_name;
    int ram;            // RAM in Gb
    int storage;        // Storage in Gb
    double cpu_clock;   // CPU clock in Ghz
} thinkpad;

typedef struct _card {
    thinkpad *thinkpad;
    struct _card *next;
} card;

/*
 * @author Lian Studer
 */
thinkpad *new_thinkpad(char *name, int ram, int storage, double cpu_clock) {
    thinkpad *new_thinkpad = (thinkpad *)malloc(sizeof(thinkpad));
    new_thinkpad->model_name = name;
    new_thinkpad->ram = ram;
    new_thinkpad->storage = storage;
    new_thinkpad->cpu_clock = cpu_clock;
    return new_thinkpad;
}

/*
 * @author Lian Studer
 */
card *new_card(thinkpad *model) {
    card *new_card = (card *)malloc(sizeof(card));
    new_card->thinkpad = model;
    new_card->next = NULL; 
    return new_card;
}

void append_card(card *top_card, card *new_card) {
    new_card->next = top_card->next;
    top_card->next = new_card;
}

/*
 * @author Lian Studer
 */
card *generate_cards() {
    card *head = NULL;

    thinkpad *thinkpad1 = new_thinkpad("X220", 8, 256, 2.4);
    card *card1 = new_card(thinkpad1);
    head = card1;

    thinkpad *thinkpad2 = new_thinkpad("X420", 8, 512, 2.8);
    card *card2 = new_card(thinkpad2);
    head->next = card2;
    head = card2;

    thinkpad *thinkpad3 = new_thinkpad("T60", 4, 64, 1.8);
    card *card3 = new_card(thinkpad3);
    head->next = card3;
    head = card3;

    head->next = card1;
    return card1;
}

/*
 * @author Lian Studer
 */
bool run_game() { 
    card *top_card = generate_cards();
    return true;
}

/*
 * @author Lian Studer
 */
int main() {
    return run_game();
}
