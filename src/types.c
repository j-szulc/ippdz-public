/** @file
 * Type definitions
 *
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

struct FieldData;

typedef struct FieldData *Field;

typedef struct FieldData {
    uint32_t owner;       /**< Either zero (in which case the field is free)
                               or index of the player whose pawn is there */
    bool bfs_flag;        /**< Temporary flag used by @ref bfs
                               and @ref bfs_visit_field */
} FieldData;

typedef struct OwnerData {
    bool golden_move_used; /**< Has this player already used the golden move */
    uint64_t busy_fields;  /**< How many fields
                                does this player have a pawn on */
    int64_t busy_areas;    /**< How many areas do the fields
                                owned by this real player form.
                                For the fake player it's always 0.*/
} OwnerData;

typedef OwnerData *Owner;

typedef struct gamma {
    uint32_t width;              /**< Width of the board */
    uint32_t height;             /**< Height of the board */
    uint32_t max_areas;          /**< Maximal number of areas
                                      player is allowed to have */
    FieldData **board;           /**< FieldData for each field of the board
                                     To access FieldData for (x,y)
                                     execute board[x][y] */
    OwnerData *owners;           /**< Player data for each owner
                                     (size: @p number_of_player + 1) */
    uint32_t number_of_players;  /**< Number of the real players */
} gamma_t;

typedef struct Position {
    int64_t x;
    int64_t y;
} Position;

