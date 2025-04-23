#include <stdio.h>     
#include <string.h>     
#include <stdlib.h>     

// ANSI color codes for terminal text color
const char * const GREEN = "\x1b[32m";   // Green text
const char * const YELLOW = "\x1b[33m";  // Yellow text
const char * const WHITE = "\x1b[0m";    // Reset to default text color
const char *current = WHITE;            // Tracks the current text color

// Function to change terminal text color only if it's different from the current
void setColour(const char *colour) {
    if (current == colour) return;      // Avoid redundant color changes
    printf("%s", colour);               // Output ANSI color code
    current = colour;                   // Update current color
}

int main(int argc, char **argv) {
    // Check for correct number of command-line arguments
    if (argc != 2) {
        printf("Invalid number of command line arguments\n");
        return 1;                       // Exit with error code
    }

    const char *theWord = argv[1];      // Target word to guess
    int size = strlen(theWord);         // Length of the word
    int guesses = 0, guessed = 0;       // Track guess count and success state

    // Allocate memory for user guess and helper arrays
    char *word = malloc(size + 1);      // User's guess buffer
    int *covered = malloc(size * sizeof(int));        // Tracks matched letters in target word
    int *guessCovered = malloc(size * sizeof(int));   // Tracks matched letters in guess

    // Loop for up to 6 guesses or until word is guessed
    while (!guessed && guesses < 6) {
        printf("Enter guess: ");
        
        // Read user input, max size + newline + null
        if (!fgets(word, size + 2, stdin)) {
            break;                      // Stop if input fails
        }

        word[strcspn(word, "\n")] = '\0';  // Remove newline character from input

        // Check if guess length matches target word
        if (strlen(word) != size) {
            printf("Invalid guess, guess length must match word length\n");
            continue;                   // Ask for guess again
        }

        // Reset tracking arrays before comparing guess
        memset(covered, 0, size * sizeof(int));        // Reset match tracking in target
        memset(guessCovered, 0, size * sizeof(int));   // Reset match tracking in guess

        // First pass: mark exact character matches (green)
        for (int i = 0; i < size; ++i) {
            if (word[i] == theWord[i]) {
                covered[i] = 1;
                guessCovered[i] = 1;
            }
        }

        // Second pass: check for partial matches (yellow) and print with color
        for (int i = 0; i < size; ++i) {
            if (guessCovered[i]) {
                setColour(GREEN);       // Exact match
            } else {
                int found = 0;
                for (int j = 0; j < size; ++j) {
                    // Check unmatched target characters for a match
                    if (!covered[j] && !guessCovered[i] && word[i] == theWord[j]) {
                        covered[j] = 1; // Mark this character as matched
                        found = 1;
                        break;
                    }
                }
                setColour(found ? YELLOW : WHITE);     // Yellow for partial, white otherwise
            }
            printf("%c", word[i]);      // Print character in correct color
        }
        printf("\n");
        setColour(WHITE);               // Reset terminal color

        guesses++;                      // Increment guess count

        if (strcmp(word, theWord) == 0) guessed = 1;  // Check if word is guessed
    }

    // Display result based on whether word was guessed or not
    if (guessed) {
        printf("Finished in %d guesses\n", guesses);
    } else {
        printf("Failed to guess the word: %s\n", theWord);
    }

    // Free allocated memory
    free(word);
    free(covered);
    free(guessCovered);

    return 0;                           
}
