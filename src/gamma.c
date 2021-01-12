#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "types.c"

uint64_t gamma_busy_fields(gamma_t *g, uint32_t player) {
    if(g == NULL)
        return 0;

    if (player == 0 ||
        player > g->number_of_players)
        return 0;
    else
        return g->owners[player].busy_fields;
}

bool gamma_golden_possible(gamma_t *g, uint32_t player) {
    if(g == NULL)
        return false;

    bool result = false;

    for (uint32_t i = 1; i <= g->number_of_players; i++) {
        if (i != player && g->owners[i].busy_fields > 0)
            result = !g->owners[player].golden_move_used;
    }

    return result;
}