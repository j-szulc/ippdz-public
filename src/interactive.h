/** @file
 * The interface of the interactive mode of the game gamma
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "types.h"

/** @brief Interactive mode of the gamma game
 * Run the interactive mode until Ctrl-D is pressed
 * or no player has a valid move (i.e. @p gamma_free_fields == 0)
 * or an error has occured
 * @param g         - pointer to the structure storing the game state.
 */
void interactive(gamma_t *g);

#endif //INTERACTIVE_H
