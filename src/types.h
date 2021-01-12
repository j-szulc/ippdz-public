/** @file
 * Type declarations
 *
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

struct FieldData;

/** @brief Pointer to the structure storing a field's data
 */
typedef struct FieldData *Field;

/** @brief Structure for storing field data
 *
 * By "owner" we mean either a real player (with index > 0)
 * or a fake player (with index == 0).
 *
 * Fake player is a virtual player that owns all the fields
 * which do not have a pawn on them
 *
 * Initially the board is empty, which means that every field is owned
 * by the fake player.
 *
 * By "player" we'll further mean a real player.
 */
typedef struct FieldData FieldData;

/** @brief Structure for storing owner's data
 *
 * For information on what "owner" is, check @ref FieldData.
 * For more information on @p busy_areas, check @ref are_in_the_same_area.
 *
 * For performance purposes, areas owned by the fake player are not count.
 */
typedef struct OwnerData OwnerData;

/** @brief Pointer to the structure storing an owner's data.
 */
typedef OwnerData *Owner;

/** @brief Structure for storing game data.
 *
 * @p players[0] stores the data of the fake player (see @ref FieldData).
 *
 * @p players[0]->busy_fields denotes the number of fields
 *                            which do not have a pawn on them.
 *
 * @p players[1] - @p players[@p number_of_players]
 * store data of the real players
 */
typedef struct gamma gamma_t;

/** @brief Structure for storing a 2D position on the board
 */
typedef struct Position Position;

#endif //TYPES_H
