/** @file
 * Implementation of the interface print.h
 * for representing the game state in a human-readable format
 *
 * Original interface:
 * (functions gamma_*)
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.03.2020
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gamma.h"
#include "types.c"

/** @brief Returns the number of digits of a given number.
 *
 * @param[in] number – a non-negative number
 * @return The number of digits of @p number in the decimal system.
 */
uint32_t number_of_digits(uint32_t number) {
    return snprintf(NULL, 0, "%u", number);
}

char *owner_to_str(uint32_t owner) {
    char *result = malloc(number_of_digits(owner) + 1);
    char *result_beginning = result;

    if (owner == 0) {
        result[0] = '.';
        result++;
    } else {
        result += sprintf(result, "%u", owner);
    }

    *result = '\0';

    return result_beginning;
}

char *gamma_board(gamma_t *g) {
    if (g == NULL)
        return NULL;

    uint32_t max_player_length = number_of_digits(g->number_of_players);

    uint32_t row_padding;
    if (max_player_length == 1)
        row_padding = 0;
    else
        row_padding = 1;

    uint32_t column_width = max_player_length;
    uint32_t row_width = column_width * (g->width)
                         + row_padding * (g->width - 1)
                         + 1;

    char *board = malloc(row_width * g->height + 1);
    char *board_beginning = board;

    // y needs to be signed, so that decrementing zero does not overflow
    // int32_t y would not be sufficient to store large values of
    // g->height - 1, which is an uint64_t
    for (int64_t y = g->height - 1; y >= 0; y--) {
        for (uint32_t x = 0; x < g->width; x++) {

            uint32_t owner = g->board[x][y].owner;
            char *owner_str = owner_to_str(owner);

            // Print with padding
            board += sprintf(board,
                             "%*s%s",
                             column_width - (uint32_t) strlen(owner_str), "",
                             owner_str);

            free(owner_str);

            if (x < g->width - 1)
                for (uint32_t k = 0; k < row_padding; k++)
                    board += sprintf(board, " ");

        }

        board += sprintf(board, "\n");
    }

    *board = '\0';

    return board_beginning;
}