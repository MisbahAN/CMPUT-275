#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Collaborated with: Muhammad Ayaan Hafeez

// Define a structure for a set of integers, storing a dynamic array of items,
// the current number of items, and the allocated capacity.
typedef struct {
    int *items;      // Dynamic array holding the set elements
    int count;       // Current number of elements in the set
    int capacity;    // Current capacity of the dynamic array
} IntSet;

// Declare two sets, one for 'x' and one for 'y'
IntSet setOne = {NULL, 0, 0};
IntSet setTwo = {NULL, 0, 0};

// Performs a binary search to find the correct insert index for a number.
// If the number already exists, its index is returned.
int getInsertIndex(IntSet *s, int number) {
    int low = 0;
    int high = s->count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (s->items[mid] == number) {
            return mid;
        } else if (s->items[mid] < number) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

// Inserts a number into the set in sorted order, if it is not already present.
void insertIntoSet(IntSet *s, int number) {
    if (s->count > 0) {
        int pos = getInsertIndex(s, number);
        if (pos < s->count && s->items[pos] == number) {
            return; // Number already exists, do nothing.
        }
        // If the set is full, double its capacity.
        if (s->count >= s->capacity) {
            int newCapacity = s->capacity == 0 ? 4 : s->capacity * 2;
            int *newItems = realloc(s->items, newCapacity * sizeof(int));
            if (!newItems) return;
            s->items = newItems;
            s->capacity = newCapacity;
        }
        // Shift elements to make room for the new number.
        for (int i = s->count; i > pos; i--) {
            s->items[i] = s->items[i - 1];
        }
        s->items[pos] = number;  // Insert the number at the correct position.
        s->count++;
    } else {
        // For an empty set, allocate initial space and insert the number.
        if (s->capacity == 0) {
            s->items = malloc(4 * sizeof(int));
            if (!s->items) return;
            s->capacity = 4;
        }
        s->items[0] = number;
        s->count = 1;
    }
}

// Removes a number from the set if it exists.
void deleteFromSet(IntSet *s, int number) {
    int low = 0, high = s->count - 1, pos = -1;
    // Binary search for the number in the set.
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (s->items[mid] == number) {
            pos = mid;
            break;
        } else if (s->items[mid] < number) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (pos == -1) return;  // Number not found; nothing to remove.
    // Shift elements left to fill the gap.
    for (int i = pos; i < s->count - 1; i++) {
        s->items[i] = s->items[i + 1];
    }
    s->count--;
}

// Prints the elements of the set in increasing order, separated by spaces.
void displaySet(IntSet *s) {
    for (int i = 0; i < s->count; i++) {
        printf("%d", s->items[i]);
        if (i != s->count - 1) {
            printf(" ");
        }
    }
    if (s->count > 0) {
        printf("\n");
    }
}

// Computes and prints the union of setOne and setTwo.
// The union contains every element present in either set.
void handleUnion() {
    int *unionItems = malloc((setOne.count + setTwo.count) * sizeof(int));
    if (!unionItems) return;
    int uCount = 0, i = 0, j = 0;
    // Merge the two sorted sets into the union array.
    while (i < setOne.count && j < setTwo.count) {
        if (setOne.items[i] < setTwo.items[j]) {
            unionItems[uCount++] = setOne.items[i++];
        } else if (setOne.items[i] > setTwo.items[j]) {
            unionItems[uCount++] = setTwo.items[j++];
        } else {
            unionItems[uCount++] = setOne.items[i++];
            j++;
        }
    }
    // Append any remaining elements from setOne.
    while (i < setOne.count) unionItems[uCount++] = setOne.items[i++];
    // Append any remaining elements from setTwo.
    while (j < setTwo.count) unionItems[uCount++] = setTwo.items[j++];
    // Print the union result.
    for (int k = 0; k < uCount; k++) {
        printf("%d", unionItems[k]);
        if (k < uCount - 1) printf(" ");
    }
    if (uCount > 0) printf("\n");
    free(unionItems);
}

// Computes and prints the intersection of setOne and setTwo.
// The intersection contains only elements that appear in both sets.
void handleIntersection() {
    int maxSize = setOne.count < setTwo.count ? setOne.count : setTwo.count;
    int *interItems = malloc(maxSize * sizeof(int));
    if (!interItems) return;
    int iCount = 0, i = 0, j = 0;
    // Traverse both sets to find common elements.
    while (i < setOne.count && j < setTwo.count) {
        if (setOne.items[i] < setTwo.items[j]) {
            i++;
        } else if (setOne.items[i] > setTwo.items[j]) {
            j++;
        } else {
            interItems[iCount++] = setOne.items[i++];
            j++;
        }
    }
    // Print the intersection result.
    for (int k = 0; k < iCount; k++) {
        printf("%d", interItems[k]);
        if (k < iCount - 1) printf(" ");
    }
    if (iCount > 0) printf("\n");
    free(interItems);
}

// Main function processes user commands to modify and display sets.
int main() {
    char cmd;
    // Read commands until the 'q' (quit) command is received.
    while (scanf(" %c", &cmd) == 1 && cmd != 'q') {
        if (cmd == 'a' || cmd == 'r') { // 'a' to add, 'r' to remove an element.
            char target[2];
            int number;
            if (scanf(" %1s %d", target, &number) != 2) continue;
            // Determine which set to operate on based on the target: 'x' corresponds to setOne, 'y' to setTwo.
            IntSet *currentSet = (target[0] == 'x') ? &setOne : (target[0] == 'y') ? &setTwo : NULL;
            if (!currentSet) continue;
            if (cmd == 'a') insertIntoSet(currentSet, number);
            else deleteFromSet(currentSet, number);
        } else if (cmd == 'p') { // 'p' to print a set.
            char target[2];
            if (scanf(" %1s", target) != 1) continue;
            IntSet *currentSet = (target[0] == 'x') ? &setOne : (target[0] == 'y') ? &setTwo : NULL;
            if (currentSet) displaySet(currentSet);
        } else if (cmd == 'u') { // 'u' to compute and print the union of the two sets.
            handleUnion();
        } else if (cmd == 'i') { // 'i' to compute and print the intersection of the two sets.
            handleIntersection();
        }
    }
    // Clean up: free the dynamic arrays for both sets.
    free(setOne.items);
    free(setTwo.items);
    return 0;
}