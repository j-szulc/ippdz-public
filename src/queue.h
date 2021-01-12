/** @file
 * Interface for managing the queue
 *
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

/** @brief Stores data of the whole queue.
 */
typedef struct QueueData *Queue;

/** @brief Allocates an empty queue.
 *
 * @return Empty queue.
 *         i.e. pointer to the newly allocated QueueData
 *         or NULL if the allocation has failed
 */
Queue queue_new();

/** @brief Checks if Queue @p queue is empty.
 *
 * @param queue         – pointer to the structure storing queue data
 */
bool queue_empty(Queue queue);

/** @brief Insert @p value at the end of @p queue.
 *
 * @param queue         – pointer to the structure storing queue data
 * @param value         – value to append at the end of the queue
 */
void queue_insert(Queue queue, Position value);

/** @brief Remove the first value from @p queue.
 *
 * Throws error if @p queue is empty.
 * @param queue         – pointer to the structure storing queue data
 * @return The value removed from @p queue.
 */
Position queue_pop(Queue queue);

/** @brief Frees @p queue from the memory.
 *
 * Does nothing if @p queue == NULL.
 * @param queue         – pointer to the structure storing queue data
 */
void queue_delete(Queue queue);

#endif //QUEUE_H
