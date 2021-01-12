/** @file
 * Implementation of allocation and freeing methods for game "Gamma".
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
#include "gamma.h"
#include "memory.h"
#include "types.c"

/** @brief Allocates a 2D array.
 *
 * Allocates a 2D array of variables, each having size @p size.
 * The array must be freed by @ref free_2d.
 *
 * For example, to access the top-right corner of the board use
 * @p result[width-1][height-1]
 *
 * @param width   –  width of the array (scope of the first coordinate)
 * @param height      –  width of the array (scope of the second coordinate)
 * @param size        –  size of a single cell in the array
 *
 * @return Pointer to the 2D array or NULL if the allocation has failed.
 */
static void **calloc_2d(uint32_t width, uint32_t height, size_t size) {

    void **result = malloc(sizeof(void *[width]));
    if (result == NULL) {
        return NULL;
    } else {
        for (uint32_t i = 0; i < width; i++) {
            result[i] = calloc(height, size);
            if (result[i] == NULL)
                return NULL;
        }
        return result;
    }
}

/** @brief Frees a 2D array.
 *
 * Frees a 2D array created by @ref calloc_2d.
 * Does nothing if @p toFree is NULL.
 *
 * @param toFree      –  pointer to the 2D array,
 *                       a return value of @ref calloc_2d
 * @param width       –  width of the array (scope of the first coordinate),
 *                       value given to @ref calloc_2d when creating the array
 */
static void free_2d(void **toFree, uint32_t width) {
    if (toFree != NULL) {
        for (uint32_t i = 0; i < width; i++) {
            free(toFree[i]);
        }
        free(toFree);
    }
}

gamma_t *gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas) {

    if (width == 0 || height == 0 || players == 0 || areas == 0)
        return NULL;

    gamma_t *result = malloc(sizeof(gamma_t));
    if (result == NULL)
        return NULL;

    result->width = width;
    result->height = height;
    result->max_areas = areas;

    result->owners = calloc((int64_t) players + 1, sizeof(OwnerData));
    result->number_of_players = players;

    result->board = (FieldData **) calloc_2d(width, height, sizeof(FieldData));

    if (result->owners == NULL || result->board == NULL) {
        return NULL;
    } else {
        /// result->owners[0].busy_fields stores fields
        /// which do not have a pawn on them
        /// (see @ref gamma_t)
        /// Initially no field has a pawn on them
        result->owners[0].busy_fields = width * height;
        return result;
    }
}

void gamma_delete(gamma_t *g) {
    if (g != NULL) {
        free(g->owners);
        free_2d((void **) g->board, g->width);
        free(g);
    }
}
