#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Collaborated with: Muhammad Ayaan Hafeez

// Checks if a character is a whitespace (space, tab, newline, etc.)
int is_whitespace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

// Validates if the string represents a valid integer number.
// It handles an optional leading '+' or '-' sign and then ensures all remaining characters are digits.
int is_valid_number(const char *s) {
    if (*s == '+' || *s == '-') {
        s++;  // Skip the sign
    }
    if (*s == '\0') {
        return 0; // Only a sign is invalid 
    }
    while (*s) {
        if (*s < '0' || *s > '9') {
            return 0; // Found a non-digit character, so it's not a valid number
        }
        s++;
    }
    return 1; // All characters are digits, so it's a valid number
}

// Checks if the string is one of the valid operators: 'p' for plus, 's' for subtract,
// '*' for multiplication, or '/' for division.
int is_operator(const char *s) {
    return strcmp(s, "p") == 0 || strcmp(s, "s") == 0 || strcmp(s, "*") == 0 || strcmp(s, "/") == 0;
}

int main() {
    char **array = NULL;      // Dynamic array to hold tokens (strings)
    size_t capacity = 4;      // Initial capacity for the tokens array
    size_t size = 0;          // Current number of tokens stored

    // Allocate initial memory for the array of string pointers.
    array = malloc(capacity * sizeof(char *));
    if (!array) {
        perror("Initial array allocation failed");
        return 1;
    }

    // Loop to read tokens from standard input until EOF is encountered.
    while (1) {
        int c;
        // Skip leading whitespace characters.
        while ((c = getchar()) != EOF && is_whitespace(c));

        if (c == EOF) break; // Exit loop if end-of-file is reached

        size_t buffer_size = 4; // Initial size for the word buffer
        // Allocate memory for a new word (token)
        char *word = malloc(buffer_size);
        if (!word) {
            perror("Word buffer allocation failed");
            goto cleanup;
        }
        
        size_t len = 0;
        // Store the first non-whitespace character in the word buffer.
        word[len++] = (char)c;

        // Read the rest of the token until a whitespace or EOF is encountered.
        while (1) {
            c = getchar();
            if (c == EOF || is_whitespace(c)) break;
            
            // If the buffer is full, double its size using realloc.
            if (len + 1 >= buffer_size) {
                buffer_size *= 2;
                char *temp = realloc(word, buffer_size);
                if (!temp) {
                    perror("Word buffer reallocation failed");
                    free(word);
                    goto cleanup;
                }
                word = temp;
            }
            // Append the character to the word buffer.
            word[len++] = (char)c;
        }
        word[len] = '\0'; // Null-terminate the string to complete the token

        // Validate the token: it must be either a valid operator or a valid number.
        if (!is_operator(word) && !is_valid_number(word)) {
            printf("Invalid input - invalid operator %s\n", word);
            free(word);
            goto cleanup;
        }

        // If the tokens array is full, double its capacity.
        if (size >= capacity) {
            capacity *= 2;
            char **temp = realloc(array, capacity * sizeof(char *));
            if (!temp) {
                perror("Array reallocation failed");
                free(word);
                goto cleanup;
            }
            array = temp;
        }

        // Save the token into the array.
        array[size++] = word;
        if (c == EOF) break;
    }

    // Allocate memory for the stack, which will be used to evaluate the RPN expression.
    int *stack = malloc(size * sizeof(int));
    if (!stack) {
        perror("Stack allocation failed");
        goto cleanup;
    }
    int stack_size = 0; // Initialize the stack size (number of elements in the stack)

    // Process each token from the array to evaluate the RPN expression.
    for (size_t i = 0; i < size; i++) {
        const char *token = array[i];
        // If the token is an operator, pop two operands from the stack, perform the operation,
        // and push the result back onto the stack.
        if (is_operator(token)) {
            if (stack_size < 2) {
                printf("Invalid input - operator without enough operands\n");
                free(stack);
                goto cleanup;
            }
            int b = stack[--stack_size]; // Pop the top operand (right operand)
            int a = stack[--stack_size]; // Pop the next operand (left operand)
            int result;
            // Determine the operation based on the operator token.
            if (strcmp(token, "p") == 0) {
                result = a + b;
            } else if (strcmp(token, "s") == 0) {
                result = a - b;
            } else if (strcmp(token, "*") == 0) {
                result = a * b;
            } else if (strcmp(token, "/") == 0) {
                result = a / b;
            }
            // Push the result of the operation back onto the stack.
            stack[stack_size++] = result;
        } else {
            // If the token is a number, convert it to an integer and push it onto the stack.
            int num = atoi(token);
            stack[stack_size++] = num;
        }
    }

    // After processing all tokens, there should be exactly one number on the stack.
    // If not, the expression was invalid.
    if (stack_size != 1) {
        printf("Invalid input - expression has too many operands\n");
        free(stack);
        goto cleanup;
    }

    // Print the final result of the evaluated RPN expression.
    printf("%d\n", stack[0]);
    free(stack);

cleanup:
    // Free all allocated memory for the tokens.
    for (size_t i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}