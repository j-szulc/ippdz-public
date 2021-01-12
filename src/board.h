/** @file
 * Interface for managing board and areas
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#ifndef BOARD_H
#define BOARD_H

#include "types.h"
#include "queue.h"

/** @brief Returns the field given its position.
 *
 * @param g             – pointer to the structure storing the game state
 * @return Field with postion @p postion
 * or NULL if @p position is not @ref inside_board.
 */
Field get_field(gamma_t *g, Position position);

/** @brief Checks if fields with positions @p a and @p b lie in the same area
 *
 * @p a and @p b are said to be in the same area iff
 * one can get from @a to @b
 * using only fields of the same player
 * (especially fields @p a and @p b need to belong to the same player)
 *
 * If both @p a and @p b are free (i.e. do not have a pawn on them)
 * the result says whether it's possible to get from @a to @b
 * using only free fields.
 *
 * @param g                    – pointer to the structure storing the game state
 * @param a                    – the first position
 * @param g                    – the second position
 * @return True if @p a and @p b lie in the same area, false otherwise.
 */
bool are_in_the_same_area(gamma_t *g, Position a, Position b);

/** @brief Counts neighbouring areas
 *
 * Counts all areas that contain at least
 * one of the neighbours of @p position and belong to the player
 * with index @p player.
 * For more information on areas, check @ref are_in_the_same_area.
 * @param g                    – pointer to the structure storing the game state
 * @param player               – player whose areas to count
 * @param position             – position whose neighbouring areas are counted
 * @param include_center       – if true, consider @p position
 *                               as a neighbour itself
 *                               (i.e. also count areas that contain @p postion
 *                               itself but do not contain any of its proper
 *                               neighbours)
 * @return Number of neighbouring areas.
 *         Note that if @p player is not a real player
 *         (e.g. @p player==0), the function returns 0.
 */
uint32_t neighbouring_areas(gamma_t *g, uint32_t player,
                            Position position, bool include_center);


#endif //BOARD_H
