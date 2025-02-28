#include <stdio.h>
#include <stdlib.h>

int getValue(char roman) {
    switch (roman) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;  // Handle unexpected characters
    }
}

int main() {
    char current_character = getchar();
    int total = 0;
    char previous_Char = current_character;

    // Read until EOF or a newline is encountered
    while ((current_character = getchar()) != EOF && current_character != '\n') {
        if (getValue(current_character) == 0) continue;  // Ignore invalid characters like spaces

        int x = getValue(previous_Char);
        int y = getValue(current_character);

        if (x >= y) {
            total += x;
        } else {
            total -= x;
        }

        previous_Char = current_character;
    }

    total += getValue(previous_Char);  // Add the last character value

    printf("%d\n", total);
    return 0;
}
