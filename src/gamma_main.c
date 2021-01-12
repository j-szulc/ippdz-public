/** @file
 * The main file for the second part of the task
 * Provides an interface for accessing both batch and interactive modes
 *
 * Implementation:
 * @author Jakub Szulc <gihtub.com/j-szulc>
 */

// If not defined, results in a warning with getline
#define  _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "gamma.h"
#include "types.c"
#include "interactive.h"
#include "batch.h"

/**@brief Maximum allowed number of tokens
 * i.e. more tokens means the input is invalid
 */
#define MAX_NUMBER_OF_TOKENS 5

/** @brief Splits string into tokens
 * Splits @p string with respect to the whitespaces.
 * Function replaces whitespaces in  @p string with \0.
 * e.g. parse("a  bc d") returns {"a","bc","d",NULL}
 * @param string       – input to split into tokens
 * @return Pointer to a NULL terminated array of tokens. Each token is a pointer
 * to some part of the original @p string. The resulting array
 * has no more elements than MAX_NUMBER_OF_TOKENS + 1 ( +1 is for the NULL ).
 * The resulting array must be freed manually.
 */
static char **parse(char *string) {
    // Important - initializes tokens as an array of NULLs
    char **tokens = calloc(MAX_NUMBER_OF_TOKENS + 1, sizeof(char *));
    if (tokens == NULL)
        return NULL;

    for (int i = 0; i < MAX_NUMBER_OF_TOKENS + 1 && *string != '\0'; i++) {
        // Skip all whitespace characters
        while (*string != '\0' && isspace(*string)) {
            *string = '\0';
            string++;
        }

        // Save position
        if (*string != '\0')
            tokens[i] = string;

        // Skip all non-whitespace characters
        while (*string != '\0' && !isspace(*string))
            string++;
    }

    return tokens;
}

/** @brief Converts string to uint32_t
 * The function tries to convert @p str to uint32_t. If it suceeds,
 * the result is saved in @p output
 * @param str           - string to be converted
 * @param output        - where to save the output
 * @return true if the conversion was successful, false otherwise
 */
static bool strToInt(char *str, uint32_t *output) {
    if (str == NULL)
        return false;

    uint64_t result = 0;
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9' && result <= UINT32_MAX)
            result = 10 * result + (*str - '0');
        else
            return false;
        str++;
    }
    if (result <= UINT32_MAX)
        *output = result;
    return result <= UINT32_MAX;
}

/** @brief enum for storing current state of the game
 *  NO_MODE      - No mode has been selected yet
 */
enum Mode {
    NO_MODE, BATCH, INTERACTIVE
};

/** @brief Replaces the first newline character found in @p string with 0
 * @param string
 * @return true if newline has been found and false otherwise
 */
static bool stripNewline(char *string) {
    char *newlinePtr = strchr(string, '\n');
    if (newlinePtr != NULL) {
        *newlinePtr = '\0';
        return true;
    } else {
        return false;
    }
}

/** @brief Returns the number of tokens given by @p parse
 * @param tokens        - output of @p parse function
 * @return minimum of:
 * number of non-NULL elements of @p tokens
 * MAX_NUMBER_OF_TOKENS+1
 */
uint32_t numberOfTokens(char **tokens) {
    uint32_t result = 0;
    while (result <= MAX_NUMBER_OF_TOKENS + 1 &&
           *(tokens++) != NULL)
        result++;
    return result;
}


/** @brief The main function
 */
int main(int argc, char **argv) {

    FILE *input = stdin;
    if (argc > 1) {
        input = fopen(argv[1], "r");
    }

    char *buffer = NULL;
    size_t len = 0;
    enum Mode mode = NO_MODE;

    gamma_t *g = NULL;

    for (uint32_t i = 1; getline(&buffer, &len, input) != -1; i++) {

        stripNewline(buffer);

        // Flag to indicate whether the input is correct
        bool correct = true;

        if (*buffer != '\0' && *buffer != '#') {
            // If it's not a comment or an empty line

            char **tokens = parse(buffer);
            if (tokens == NULL)
                // malloc failure
                return 0;

            if (numberOfTokens(tokens) >= 1) {
                uint32_t numberOfArgs = numberOfTokens(tokens) - 1;

                // Convert string tokens to integer arguments
                uint32_t *args = malloc(numberOfArgs * sizeof(uint32_t));
                if (args == NULL)
                    // malloc failure
                    return 0;

                for (uint32_t j = 0; j < numberOfArgs; j++)
                    // Convert until one of the arguments is invalid
                    correct = correct && strToInt(tokens[j + 1], &args[j]);

                if (strlen(tokens[0]) == 1 && correct) {
                    char command = tokens[0][0];

                    if (mode == BATCH) {
                        correct = batch(g, command, args, numberOfArgs);
                    } else if ((command == 'B' || command == 'I') &&
                               numberOfArgs == 4 &&
                               (g = gamma_new(args[0], args[1],
                                              args[2], args[3])) != NULL) {

                        switch (command) {
                            case 'B':
                                mode = BATCH;
                                break;
                            case 'I':
                                mode = INTERACTIVE;
                        };
                        printf("OK %u\n", i);
                    } else {
                        // Invalid command
                        correct = false;
                    }
                } else {
                    // Command consists of more than one character
                    // or integer conversion has failed
                    correct = false;
                }
                free(args);
            } else {
                // not a comment nor an empty line
                // but there are only whitespaces
                correct = false;
            }
            free(tokens);
        }

        if (!correct)
            fprintf(stderr, "ERROR %u\n", i);


        if (mode == INTERACTIVE) {
            interactive(g);
            break;
        }
    }

    free(buffer);
    gamma_delete(g);

    return 0;
}