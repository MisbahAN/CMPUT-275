#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
    if (current == colour) return;
    printf("%s", colour);
    current = colour;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Invalid number of command line arguments\n");
        return 1;
    }

    const char *theWord = argv[1];
    int size = strlen(theWord);
    if (size >12){
        printf("Code longer than 12 characters, invalid input\n");
        return 1;
    }
    int guesses = 0, guessed = 0;
    char *word = malloc(size + 1);
    int *covered = malloc(size * sizeof(int));
    int *guess_Covered = malloc(size * sizeof(int));

    while (!guessed && guesses < 7) {
        printf("Enter guess: ");
        scanf("%s", word);

        if (strlen(word) != size) {
            printf("Invalid guess, guess length must match word length\n");
            break;
        }

        memset(covered, 0, size * sizeof(int));
        memset(guess_Covered, 0, size * sizeof(int));

        for (int i = 0; i < size; ++i) {
            if (word[i] == theWord[i]) {
                covered[i] = 1;
                guess_Covered[i] = 1;
            }
        }

        for (int i = 0; i < size; ++i) {
            if (guess_Covered[i]) {
                setColour(GREEN);
            } else {
                int found = 0;
                for (int j = 0; j < size; ++j) {
                    if (!covered[j] && !guess_Covered[i] && word[i] == theWord[j]) {
                        covered[j] = 1;
                        found = 1;
                        break;
                    }
                }
                setColour(found ? YELLOW : WHITE);
            }
            printf("%c", word[i]);
        }
        printf("\n");
        setColour(WHITE);
        
        guesses++;
        if (strcmp(word, theWord) == 0) guessed = 1;
    }
    if (strlen(word)==size){
      if (guessed) {
          printf("Finished in %d guesses\n", guesses);
      }
      else {
          printf("Failed to guess the word: %s\n", theWord);
      }
  }
    free(word);
    free(covered);
    free(guess_Covered);

    return 0;
}