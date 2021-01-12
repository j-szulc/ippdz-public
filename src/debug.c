#include <stdlib.h>
#include <stdio.h>
#include "types.c"
#include "board.h"

void new_board(gamma_t *g, uint32_t *owners) {
    for (uint32_t y = 0; y < g->height; y++) {
        for (uint32_t x = 0; x < g->width; x++) {
            Position position = {x, y};
            Field new_field = get_field(g, position);
            new_field->owner = *(owners++);
        }
    }
}

char *flags(gamma_t *g) {
    char *result = malloc(1000);
    char *result_beginning = result;
    for (int64_t y = g->height - 1; y >= 0; y--) {
        for (uint32_t x = 0; x < g->width; x++) {
            Position position = {x, y};
            Field f = get_field(g, position);
            result += sprintf(result, "%i", f->bfs_flag);
        }
        result += sprintf(result, "\n");
    }
    return result_beginning;
}

