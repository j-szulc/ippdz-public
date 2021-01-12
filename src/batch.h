/** @file
 * The interface of the batch mode of the game gamma
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#ifndef BATCH_H
#define BATCH_H

#include "types.h"
#include "moves.h"
#include "gamma.h"

/** @brief Process a batch mode command
 * Process a batch mode command and print its return value to stdout
 * (if the command is correct)
 * @param g             - pointer to the structure storing the game state.
 * @param command       - a one-letter command
 * @param args          - array of arguments for the command
 * @param numberOfArgs  - length of @p args array
 * @return true if the command is correct, false otherwise
 */
bool batch(gamma_t *g, char command, uint32_t *args, uint32_t numberOfArgs);

#endif //BATCH_H
