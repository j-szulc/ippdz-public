/** @file
 * Interface of class for playing the game "Gamma"
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

#ifndef GAMMA_H
#define GAMMA_H

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

#include "memory.h"
#include "board.h"
#include "moves.h"
#include "print.h"

/** @brief Number of fields owned by a player.
 *
 * Returns the number of fields owned by @p player.
 * @param[in] g       – pointer to the structure storing the game state,
 * @param player      – index of the player, positive number not greater
 *                      than the value @p players given to @ref gamma_new
 * @return Number of fields owned by @p player or zero
 * if one of the parameters is invalid.
 */
uint64_t gamma_busy_fields(gamma_t *g, uint32_t player);

/** @brief Checks if a player can still make a golden move.
 *
 * Checks if @p player has not made a golden move yet
 * and there's at least one field owned by another player
 * @param[in] g       – pointer to the structure storing the game state,
 * @param player      – index of the player, positive number not greater
 *                      than the value @p players given to @ref gamma_new
 * @return @p true, if all parameters are correct
 * and @p player can still make a golden move, @p false otherwise.
 */
bool gamma_golden_possible(gamma_t *g, uint32_t player);

#endif /* GAMMA_H */
