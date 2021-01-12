/** @file
 * Implementation of the interface
 * for making moves and verifying their validity
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
#include "board.h"
#include "types.c"

/** @brief Changes the owner of the field.
 * Changes the owner of the field and updates game state.
 * The @p new_owner is either positive
 * (in which case it means a player of the same index)
 * or zero
 * (which will simply remove the existing owner's pawn).
 * For information on what "owner" means, go to @ref FieldData.
 * @param g             – pointer to the structure storing the game state
 * @param new_owner     – zero or the index of the player,
 *                        positive number not greater
 *                        than the value @p players given to @ref gamma_new
 * @param position      – position of the field whose owner is to be changed
 */
static void change_owner(gamma_t *g, uint32_t new_owner, Position position) {

    Field field = get_field(g, position);

    uint32_t old_owner = field->owner;

    int64_t new_owner_areas_before = neighbouring_areas(g, new_owner, position, true);
    int64_t old_owner_areas_before = neighbouring_areas(g, old_owner, position, true);

    field->owner = new_owner;
    g->owners[new_owner].busy_fields += 1;
    g->owners[old_owner].busy_fields -= 1;

    int64_t new_owner_areas_after = neighbouring_areas(g, new_owner, position, true);
    int64_t old_owner_areas_after = neighbouring_areas(g, old_owner, position, true);

    g->owners[new_owner].busy_areas += new_owner_areas_after - new_owner_areas_before;
    g->owners[old_owner].busy_areas += old_owner_areas_after - old_owner_areas_before;

}

/** @brief Checks if changing the owner would result in an illegal situation.
 * Checks if operation @ref change_owner would make either
 * old owner or new owner exceed the area limit.
 *
 * Note that the fake player (represented by @p new_owner == 0)
 * cannot exceed the area limit.
 * For information on what "owner" means, go to @ref FieldData.
 * @param g             – pointer to the structure storing the game state
 * @param new_owner     – zero or the index of the player,
 *                        positive number not greater
 *                        than the value @p players given to @ref gamma_new
 * @param position      – position of the field whose owner is to be changed
 */
static bool change_owner_valid(gamma_t *g, uint32_t new_owner, Position position) {
    Field field = get_field(g, position);

    if (field != NULL) {

        uint32_t old_owner = field->owner;

        change_owner(g, new_owner, position);
        bool result = (g->owners[new_owner].busy_areas <= g->max_areas) &&
                      (g->owners[old_owner].busy_areas <= g->max_areas);

        change_owner(g, old_owner, position);

        return result;
    } else {
        return false;
    }

}

/** @brief Checks if a golden move is valid (legal)
 * Checks if a golden move is valid (legal)
 * For information on what is a golden move, check @ref gamma_golden_move
 * @param g             – pointer to the structure storing the game state
 * @param player        – index of the player, positive number not greater
 *                        than the value @p players given to @ref gamma_new
 * @param position      – position where the golden move is supposed to be made
 * @return @p true, if the golden move is valid or @p false otherwise
 */
static bool golden_move_valid(gamma_t *g, uint32_t player, Position position) {
    Field field = get_field(g, position);

    return player <= g->number_of_players &&
           player > 0 &&
           !g->owners[player].golden_move_used &&
           field != NULL &&
           field->owner != 0 &&
           field->owner != player &&
           change_owner_valid(g, player, position);
}

/** @brief Checks if move is valid (legal)
 * Checks if move is valid (legal)
 * @param g             – pointer to the structure storing the game state
 * @param player        – index of the player, positive number not greater
 *                        than the value @p players given to @ref gamma_new
 * @param position      – position where the move is supposed to be made
 * @return @p true, if the move is valid or @p false otherwise
 */
static bool move_valid(gamma_t *g, uint32_t player, Position position) {
    Field field = get_field(g, position);

    return player <= g->number_of_players &&
           player > 0 &&
           field != NULL &&
           field->owner == 0 &&
           change_owner_valid(g, player, position);
}


bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if(g == NULL)
        return false;

    Position position = {x, y};
    if (golden_move_valid(g, player, position)) {
        change_owner(g, player, position);
        g->owners[player].golden_move_used = true;
        return true;
    } else {
        return false;
    }
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    if(g == NULL)
        return false;

    Position position = {x, y};
    if (move_valid(g, player, position)) {
        change_owner(g, player, position);
        return true;
    } else {
        return false;
    }
}


uint64_t gamma_free_fields(gamma_t *g, uint32_t player) {
    if(g == NULL)
        return false;

    uint64_t result = 0;
    for (uint32_t x = 0; x < g->width; x++) {
        for (uint32_t y = 0; y < g->height; y++) {
            Position position = {x, y};
            if (move_valid(g, player, position))
                result++;
        }
    }

    return result;
}



