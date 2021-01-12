/** @file
 * Interface for representing the game state
 * in a human-readable format
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

#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include "types.h"

/** @brief Returns the number of digits of a given number.
 *
 * @param[in] number – a non-negative number
 * @return The number of digits of @p number in the decimal system.
 */
uint32_t number_of_digits(uint32_t number);

/** @brief Converts a field owner to a string format
 *
 * Allocates a new c string, which must be freed by the player once used.
 *
 * If owner is a positive number (a real player) the result is just the number
 * @p
 * @param[in] owner  – non-negative number
 * @return @p owner represented in a decimal system . - if @p player > 0
 *         "."                                       - if @p player == 0
 */
char *owner_to_str(uint32_t owner);

/** @brief Returns a string describing the state of the board.
 *
 * Allocates a buffer in memory, which stores the text representation
 * of the current game state. An example is stored in gamma_test.c.
 * The buffer must be freed by the calling function.
 * @param[in] g       – pointer to the structure storing the game state.
 * @return Pointer to the allocated buffer storing the game state representation
 * or NULL if the function has failed to allocate memory.
 */
char *gamma_board(gamma_t *g);

#endif //PRINT_H
