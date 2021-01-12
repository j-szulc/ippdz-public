/** @file
 * The implementation of the interactive mode of the game gamma
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>

#include "interactive.h"
#include "print.h"
#include "gamma.h"
#include "moves.h"
#include "types.c"

/** @brief Returns the terminal dimensions
 * Usage: terminalSize().ws_col, terminalSize().ws_row
 * @return struct winsize containing terminal dimensions
 * or struct winsize such that
 * (terminalSize().ws_col == terminalSize().ws_row == 0)
 * if the command was unsuccessful
 */
struct winsize terminalSize() {
    struct winsize result;
    ioctl(0, TIOCGWINSZ, &result);
    return result;
}

/** @brief Structure storing the position on the board
 * i.e. point {0,0} is the bottom left of the screen
 */
typedef Position PositionOnBoard;

/** @brief Structure storing the position on the screen (terminal)
 * i.e. x stores the column, y stores the line
 * i.e. (1,1) is the top left corner of the terminal
 */
typedef Position PositionOnScreen;

/** Given @p positionOnBoard,
 * returns the corresponding position on the screen.
 * If the "conversion" is ambiguous,
 * i.e. the field on the board takes more than one character of space
 * it returns the leftmost.
 * The function assumes the terminal dimensions to be infinite.
 * @param g                 - pointer to the structure storing the game state.
 * @param positionOnBoard   - position to be "converted"
 * @return @p positionOnBoard "converted" to position on the screen.
 * If @p positionOnBoard is not a valid position on the board,
 * the behaviour is undefined.
 */
static PositionOnScreen gamma_board_position(gamma_t *g, PositionOnBoard positionOnBoard) {
    uint32_t max_player_length = number_of_digits(g->number_of_players);

    uint32_t row_padding;
    if (max_player_length == 1)
        row_padding = 0;
    else
        row_padding = 1;

    uint32_t column_width = max_player_length;

    PositionOnScreen result = {positionOnBoard.x * (column_width + row_padding) + 1,
                               g->height - positionOnBoard.y};

    return result;
}

/** @brief structure storing the original termios settings
 */
struct termios originalTermios;

/** @brief disable raw mode enabled by @p enableRawMode
 */
static void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios);
}

/** @brief Enable terminal raw mode
 * e.g. disable internal handling of keyboard events by the terminal
 */
static void enableRawMode() {
    tcgetattr(STDIN_FILENO, &originalTermios);
    atexit(disableRawMode);
    struct termios rawTermios = originalTermios;
    rawTermios.c_lflag &= ~(ECHO | ICANON | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTermios);
}

/** @brief Clears the terminal screen
 */
static void clearScreen() {
    printf("\x1b[1;1H\x1b[2J");
    fflush(stdout);
}

/** @brief Key codes
 *
 */
enum Keys {

    SIGILL = 4, // Ctrl-D

    SPACE = 0x20u,

    A = 0x61u,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    ARROW_UP = 0x1B5B41u,
    ARROW_DOWN,
    ARROW_RIGHT,
    ARROW_LEFT
};


void interactive(gamma_t *g) {

    enableRawMode();
    bool gameOver = false;
    PositionOnBoard cursorOnBoard = {0, g->height - 1};
    uint32_t currentPlayer = 1;

    while (!gameOver) {
        bool nextMove = false;

        // BOARD DRAWING
        char *board = gamma_board(g);

        size_t boardColumns = strchr(board, '\n') - board;
        uint32_t boardRows = g->height;

        if (terminalSize().ws_row < boardRows ||
            terminalSize().ws_col < boardColumns) {

            puts("The terminal is too small!");
            free(board);
            return;
        } else {
            clearScreen();
            printf("%s", board);
            if (terminalSize().ws_row == 0 && terminalSize().ws_col == 0)
                puts("Your terminal does not provide size information!");
        }

        free(board);

        char *golden = "";
        if (gamma_golden_possible(g, currentPlayer))
            golden = "G";

        printf("PLAYER %u %lu %lu %s",
               currentPlayer,
               gamma_busy_fields(g, currentPlayer),
               gamma_free_fields(g, currentPlayer),
               golden);

        // Buffer storing the most recent 4 bytes
        uint32_t buffer = 0;

        while (!nextMove) {
            // width of a single board column
            uint32_t columnWidth = number_of_digits(g->number_of_players);

            PositionOnScreen cursorOnScreen =
                    gamma_board_position(g, cursorOnBoard);

            // Move cursor from the first to the last character in the column
            cursorOnScreen.x += columnWidth - 1;

            printf("\x1b[%lu;%luH", cursorOnScreen.y, cursorOnScreen.x);
            fflush(stdout);

            char nextByte;

            if (read(STDIN_FILENO, &nextByte, 1) != 1) {
                // EOF
                nextMove = true;
                gameOver = true;
                break;
            }

            // Add next byte to the buffer
            buffer = (buffer << 8u) + nextByte;

            // switch depending on the last 3 bytes of the buffer
            // i.e. the most recently read 3 bytes
            switch (buffer & 0xFFFFFFu) {
                case ARROW_UP:
                    if (cursorOnBoard.y < g->height - 1)
                        cursorOnBoard.y += 1;
                    break;
                case ARROW_DOWN:
                    if (cursorOnBoard.y > 0)
                        cursorOnBoard.y -= 1;
                    break;
                case ARROW_RIGHT:
                    if (cursorOnBoard.x < g->width - 1)
                        cursorOnBoard.x += 1;
                    break;
                case ARROW_LEFT:
                    if (cursorOnBoard.x > 0)
                        cursorOnBoard.x -= 1;
            }

            switch (nextByte) {
                case SPACE:
                    nextMove = gamma_move(g, currentPlayer, cursorOnBoard.x, cursorOnBoard.y);
                    break;
                case C:
                    nextMove = true;
                    break;
                case G:
                    nextMove = gamma_golden_move(g, currentPlayer, cursorOnBoard.x, cursorOnBoard.y);
                    break;
                case SIGILL:
                    //CTRL+D
                    nextMove = true;
                    gameOver = true;
            }

        }

        int64_t skippedPlayers = -1;
        do {
            currentPlayer = currentPlayer % g->number_of_players + 1;
            skippedPlayers++;
            if (skippedPlayers >= g->number_of_players)
                gameOver = true;
        } while (!gameOver &&
                 gamma_free_fields(g, currentPlayer) == 0);

    }

    clearScreen();

    char *board = gamma_board(g);
    printf("%s", board);
    free(board);

    for (uint32_t i = 0; i < g->number_of_players; i++)
        printf("PLAYER %u %lu\n",
               i + 1,
               gamma_busy_fields(g, i + 1));
}