/** @file
 * Implementation for the interface for managing board and areas
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */


#include <stdlib.h>
#include <stdio.h>
#include "types.c"
#include "queue.h"


/** @brief Checks if positions are the same
 *
 * @return True if @p a and @p b correspond to the same point on the board
 *         and false otherwise.
 */
static bool positions_equal(Position a, Position b) {
    return a.x == b.x && a.y == b.y;
}

/** @brief Checks if a position lies inside the board.
 *
 * @param g             – pointer to the structure storing the game state
 * @return True if @p position lies inside the board and false otherwise
 */
static bool inside_board(gamma_t *g, Position position) {
    return position.x >= 0 && position.x < g->width &&
           position.y >= 0 && position.y < g->height;
}

Field get_field(gamma_t *g, Position position) {
    if (inside_board(g, position))
        return &g->board[position.x][position.y];
    else
        return NULL;
}

/** @brief An array storing all possible directions on a 2D board
 *
 * See the source for more information.
 */
static const Position directions[5] = {
        {1,  0},  // RIGHT
        {0,  1},  // UP
        {-1, 0},  // LEFT
        {0,  -1}, // DOWN
        {0,  0}   // ITSELF
};

/** @brief Returns the i-th neighbour of a position
 *
 * If i == 0            – returns the neighbour of @p position to the EAST
 * If i == 1            – returns the neighbour of @p position to the NORTH
 * If i == 2            – returns the neighbour of @p position to the WEST
 * If i == 3            – returns the neighbour of @p position to the SOUTH
 * If i == 4            – returns @p position itself
 * @param i             – integer in range [0, 4],
 *                        tells which neighbour to return
 * @return Position of the @p i-th neighbour of @p position
 */
static Position get_neighbour(Position position, int i) {
    Position result = {position.x + directions[i].x,
                       position.y + directions[i].y};
    return result;
}

/** @brief Performs a Breadth-First Search visit on a given field
 *
 * If the field with position @p position is a valid field to visit
 * (i.e. is inside board, hasn't been visited yet, and has owner @p player)
 * mark it as visited and add all of its neighbours to the queue.
 * @param g                    – pointer to the structure storing the game state
 * @param queue                – BFS queue storing positions to be visited next
 * @param position             – position to visit
 * @param owner                – index of the owner whose fields
 *                               are the only ones this function is allowed
 *                               to visit
 * @param what_means_visited   – changes the meaning of @ref FieldData.bfs_flag,
 *                               i.e. the function perceives
 *                               a Field @p f as visited iff
 *                               @p f->bfs_flag == @p what_means_visited
 */
static void bfs_visit_field(gamma_t *g, Queue queue, Position position,
                            uint32_t owner, bool what_means_visited) {

    Field field_visited = get_field(g, position);

    if (field_visited != NULL &&
        field_visited->owner == owner &&
        field_visited->bfs_flag != what_means_visited) {
        field_visited->bfs_flag = what_means_visited;

        for (int i = 0; i < 4; i++)
            queue_insert(queue, get_neighbour(position, i));
    }
}

/** @brief Tries to find a path from @p source to @p goal by performing BFS
 *
 * Tries to find a path from @p source to @p goal
 * by performing Breadth-First Search
 * @param g                    – pointer to the structure storing the game state
 * @param owner                – index of the owner whose fields
 *                               are the only ones this function is allowed
 *                               to visit
 * @param what_means_visited   – changes the meaning of @ref FieldData.bfs_flag,
 *                               i.e. the function perceives
 *                               a Field @p f as visited iff
 *                               @p f->bfs_flag == @p what_means_visited
 */
static bool bfs(gamma_t *g, Position source, Position goal, uint32_t owner,
                bool what_means_visited) {

    Queue queue = queue_new();
    if (queue == NULL)
        return false;

    queue_insert(queue, source);

    bool result = false;

    while (!result && !queue_empty(queue)) {
        Position to_visit = queue_pop(queue);
        bfs_visit_field(g, queue, to_visit, owner, what_means_visited);
        if (positions_equal(to_visit, goal))
            result = true;
    }

    queue_delete(queue);
    return result;
}

bool are_in_the_same_area(gamma_t *g, Position a, Position b) {
    uint32_t player_a = get_field(g, a)->owner;
    uint32_t player_b = get_field(g, b)->owner;

    if (player_a == player_b) {
        bool result = bfs(g, a, b, player_a, true);
        bfs(g, a, b, player_a, false);
        return result;
    } else {
        return false;
    }
}


uint32_t neighbouring_areas(gamma_t *g, uint32_t player,
                            Position position, bool include_center) {

    if (player == 0) {
        return 0;
    } else {
        uint32_t result = 0;

        uint32_t number_of_neighbours = 4;
        if (include_center)
            number_of_neighbours++;

        for (uint32_t i = 0; i < number_of_neighbours; i++) {
            Position neighbour_i_position = get_neighbour(position, i);
            Field neighbour_i = get_field(g, neighbour_i_position);

            if (neighbour_i != NULL && neighbour_i->owner == player) {
                bool is_new = true;

                for (uint32_t j = 0; j < i; j++) {
                    Position neighbour_j_position = get_neighbour(position, j);

                    if (inside_board(g, neighbour_j_position) &&
                        are_in_the_same_area(g,
                                             neighbour_i_position,
                                             neighbour_j_position)) {

                        is_new = false;
                    }
                }

                if (is_new)
                    result++;
            }
        }
        return result;
    }
}

