/** @file
 * Interface for managing the game state memory
 * (including allocation, construction, freeing and deconstruction)
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

#ifndef MEMORY_H
#define MEMORY_H

/** @brief Creates new structure storing the game state.
 *
 * Allocates memory for a new structure storing the game state.
 * Initializes the structure so that it represents the beginning state.
 * @param[in] width   – width of the board, positive number
 * @param[in] height  – height of the board, positive number,
 * @param[in] players – number of players, positive number,
 * @param[in] areas   – maximal number of areas a player can have.
 *
 * @return Pointer to the structure or NULL if memory allocation unsucessful
 * or a parameter is invalid
 */
gamma_t *gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas);

/** @brief Deletes the structure storing the game state.
 *
 * Frees the structure storing the game state from memory.
 * Does nothing if the given pointer is NULL.
 * @param[in] g       – pointer to the structure to be deleted.
 */
void gamma_delete(gamma_t *g);

#endif //MEMORY_H
