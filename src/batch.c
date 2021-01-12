/** @file
 * The implementation of the batch mode of the game gamma
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#include <stdlib.h>
#include <stdio.h>
#include "batch.h"

bool batch(gamma_t *g, char command, uint32_t *args, uint32_t numberOfArgs) {
    switch (command) {
        case 'm':
            if (numberOfArgs != 3)
                return false;
            printf("%i\n", gamma_move(g, args[0], args[1], args[2]));
            break;
        case 'g':
            if (numberOfArgs != 3)
                return false;
            printf("%i\n", gamma_golden_move(g, args[0], args[1], args[2]));
            break;
        case 'b':
            if (numberOfArgs != 1)
                return false;
            printf("%lu\n", gamma_busy_fields(g, args[0]));
            break;
        case 'f':
            if (numberOfArgs != 1)
                return false;
            printf("%lu\n", gamma_free_fields(g, args[0]));
            break;
        case 'q':
            if (numberOfArgs != 1)
                return false;
            printf("%i\n", gamma_golden_possible(g, args[0]));
            break;
        case 'p':
            if (numberOfArgs != 0)
                return false;
            char *board = gamma_board(g);
            printf("%s", board);
            free(board);
            break;
        default:
            return false;
    }
    return true;
}
