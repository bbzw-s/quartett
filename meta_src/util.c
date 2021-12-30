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
