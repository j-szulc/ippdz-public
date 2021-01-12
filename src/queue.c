/** @file
 * Implementation for the queue interface
 *
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "types.c"

struct Node;

/** @brief Stores data of a single node in the queue
 */
typedef struct NodeData {
    Position value; /**< Value stored by this node */
    struct NodeData *next; /**< Pointer to the next node in the queue*/
} *Node;


typedef struct QueueData {
    Node first; /**< Pointer to the first node of the queue,
                     NULL if the queue is empty*/
    Node last; /**< Pointer to the last node of the queue,
                    NULL if the queue is empty*/
} *Queue;

Queue queue_new() {
    Queue result = calloc(1, sizeof(struct QueueData));
    if (result == NULL)
        return NULL;

    return result;
}

bool queue_empty(Queue queue) {
    // Assert that both first and last element of queue either
    // both exist or both don't
    assert((queue->first == NULL &&
            queue->last == NULL) ||
           (queue->first != NULL &&
            queue->last != NULL));

    return queue->first == NULL &&
           queue->last == NULL;
}

void queue_insert(Queue queue, Position value) {
    Node new_node = malloc(sizeof(struct NodeData));

    new_node->value = value;
    new_node->next = NULL;

    if (queue_empty(queue)) {
        queue->first = new_node;
        queue->last = new_node;
    } else {
        queue->last->next = new_node;
        queue->last = new_node;
    }
}

Position queue_pop(Queue queue) {
    assert(!queue_empty(queue));

    Node node_popped = queue->first;
    Position result = node_popped->value;

    if (queue->first == queue->last) {
        queue->last = NULL;
    }
    queue->first = queue->first->next;

    free(node_popped);
    return result;
}

void queue_delete(Queue queue) {
    if (queue != NULL) {
        while (!queue_empty(queue)) {
            queue_pop(queue);
        }
        free(queue);
    }
}