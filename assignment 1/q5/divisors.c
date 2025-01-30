#include <stdio.h>

int main() {
    int input_number;
    scanf("%d", &input_number);
    
    if (input_number <= 0) {
        printf("\n");
        return 0;
    }

    // Special case for input_number = 1
    if (input_number == 1) {
        printf("1\n");
        return 0;
    }

    int i = 1;
    int first_divisor = 1;  // Flag to track the first divisor
    while (i < input_number) {  // Loop until input_number - 1
        if (input_number % i == 0) {
            if (first_divisor) {
                printf("%d", i); // Print without space for the first divisor
                first_divisor = 0; // After the first divisor, set flag to false
            } else {
                printf(" %d", i); // Print space before the next divisors
            }
        }
        ++i;
    }
    printf("\n"); // Ensure the output ends with a newline
    return 0;
}