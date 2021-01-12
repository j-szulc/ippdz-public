/** @file
 * Interface for making moves and verifying their validity
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

#ifndef MOVE_H
#define MOVE_H

/** @brief Makes a golden move
 *
* Places a pawn of the player on the field (@p x, @p y) taken by another player
* @param g             – pointer to the structure storing the game state
* @param player        – index of the player, positive number not greater
*                        than the value @p players given to @ref gamma_new
* @param x             – index of the column, non-negative number not greater
*                        than the value @p width from @ref gamma_new
* @param y             – index of the row, non-negative number not greater
*                        than the value @p height from @ref gamma_new
* @return @p true, if a move was made or @p false when the player has already
* used up his golden_move, move is invalid (illegal) or one of the parameters
* is invalid
*/
bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Makes a move.
 *
* Places a pawn of the player on the field (@p x, @p y).
* @param g             – pointer to the structure storing the game state
* @param player        – index of the player, positive number not greater
*                        than the value @p players given to @ref gamma_new
* @param x             – index of the column, non-negative number not greater
*                        than the value @p width from @ref gamma_new
* @param y             – index of the row, non-negative number not greater
*                        than the value @p height from @ref gamma_new
* @return @p true, if a move was made or @p false when the move is
*         invalid (illegal) or one of the parameters is invalid
*/
bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Returns the number of fields that the player can still take.
 *
 * Returns the number of fields, where @p player can place his pawn on
 * in the next turn (does not include the possibility of making a golden move)
 * (see @ref gamma_golden_move)
 * @param[in] g       – pointer to the structure storing the game state,
 * @param player      – index of the player, positive number not greater
 *                      than the value @p players given to @ref gamma_new
 * @return Number of fields that the player can still take or zero,
 * if one of the parameters is invalid.
 */
uint64_t gamma_free_fields(gamma_t *g, uint32_t player);

#endif //MOVE_H
